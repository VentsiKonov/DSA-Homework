#include "Market.h"
#include <math.h>
#include <iostream>


Market::Market(int NumberOfAllCashDecks) : N(NumberOfAllCashDecks){
	if (NumberOfAllCashDecks < 1)
		throw "You cannot have less than 1 cash deck!";

	// Init
	lockedForTicks = new int[N+1];
	for (int i = 0; i < NumberOfAllCashDecks + 1; ++i) {
		Queue<Client> j;
		cashDesks.PushBack(j);
		lockedForTicks[i] = 0;
	}
}

Market::~Market() {
	delete[] lockedForTicks;
}

MarketState Market::getMarketState() {
	MarketState ms;
	ms.numberOfCashDesk = 0;
	ms.numberOfClientsAtCashDecsk = new int[N]; // The caller of this method should delete this
	ms.numberOfClientsAtExpressCashDeck = cashDesks.PeekFront().Size();
	int n = 0;
	for (List<CashDesk>::Iterator it = ++cashDesks.Begin(); it != cashDesks.End(); ++it, ++n) {
		ms.numberOfClientsAtCashDecsk[n] = (*it).Size();
		
		if (ms.numberOfClientsAtCashDecsk[n] != 0)
			++ms.numberOfCashDesk;

	}

	return ms;

}

ClientState Market::getClientState(int ID) {

	// If expressDesk is set to be 0 in cashDesks, rework this

	ClientState cs{ 0, 0, nullptr };
	
	size_t currentDeskClients = 0;
	Client* currentClient;
	int n = 0;
	for (List<CashDesk>::Iterator it = cashDesks.Begin(); it != cashDesks.End(); ++it, ++n) {
		currentDeskClients = (*it).Size();
		
		if (currentDeskClients > 0)
			for (size_t pos = 0; pos < currentDeskClients; pos++) {
				currentClient = &(*it).Pop();

				if (currentClient->ID == ID) {
					cs.CashDeskPosition = n;
					cs.QueuePosition = pos;
					cs.client = currentClient;
				}

				(*it).Push(*currentClient);
			}
	}

	return cs;
}

void Market::AddClient(Client* clients, int number) {

	for (int i = 0; i < number; i++) {
		addClient(clients[i]);
	}

	tick();
}

CashDesk& Market::getSmallestOpenDesk(CashDesk* differentFrom) {
	size_t currentSmallest = 0;
	List<CashDesk>::Iterator i = ++cashDesks.Begin();
	CashDesk * smallestDesk = &*i;
	while (i != cashDesks.End()) {
		if (differentFrom && &(*i) == differentFrom) {
			++i;
			continue;
		}
		if ((*i).Size() != 0) {
			if (currentSmallest == 0 || currentSmallest > (*i).Size()) {
				currentSmallest = (*i).Size();
				smallestDesk = &*i;
			}
		}
		++i;
	}
	
	return *smallestDesk;
}

CashDesk* Market::getFirstClosedDesk() {
	for (List<CashDesk>::Iterator i = ++cashDesks.Begin(); i != cashDesks.End(); ++i) {
		if ((*i).Size() == 0) 
			return &*i;
	}

	return nullptr; // No closed desks left
}

void Market::addClient(const Client& client, CashDesk* notInDesk) {
	if (client.numberOfGoods > 0) {
		if (client.numberOfGoods <= 3 && cashDesks.PeekFront().Size() < 2 * N) {
			cashDesks.PeekFront().Push(client);
		}
		else {
			getSmallestOpenDesk(notInDesk).Push(client);
		}
	}
}

void Market::rearrangeFrom(CashDesk& cashDesk, size_t skipFirst) {
	size_t skipped = skipFirst;
	while (skipped--) {
		cashDesk.Push(cashDesk.Pop());
	}
	size_t queueSize = cashDesk.Size();
	for (size_t i = 0; i < queueSize - skipFirst; i++) {
		addClient(cashDesk.Pop(), &cashDesk); // TODO: Assure the client is not in the same desk he is leaving
	}
	
}

void Market::deskOperations() {
	// Try to close a desk
	size_t n = 1;
	for (List<CashDesk>::Iterator i = ++cashDesks.Begin(); i != cashDesks.End(); ++i, ++n) {
		if (lockedForTicks[n] == 0 && (*i).Size() < N / 10) { // Close desk
			rearrangeFrom(*i, 0);
			return;
		}
	}

	// Try to equalize desk queues
	for (List<CashDesk>::Iterator i = ++cashDesks.Begin(); i != cashDesks.End(); ++i) {
		if ((*i).Size() == 0) // Desk is closed
			continue;

		for (List<CashDesk>::Iterator j = ++List<CashDesk>::Iterator(i); j != cashDesks.End(); ++j) {
			if ((*j).Size() == 0 ) // Desk is closed
				continue;

			if (abs((long)(*i).Size() - (long)(*j).Size()) > N / 8) {
				// For each two queues -> compare sizes and split longer in half
				if ((*i).Size() > (*j).Size()) {
					rearrangeFrom(*i, (*i).Size() / 2);
					
				}
				else {
					rearrangeFrom(*j, (*j).Size() / 2);

				}

				return;
			}
		}
	}

	// Open a new desk
	for (List<CashDesk>::Iterator i = ++cashDesks.Begin(); i != cashDesks.End(); ++i) {
		if ((*i).Size() > N) {
			CashDesk* newDesk = getFirstClosedDesk();
			if (!newDesk) // No closed desks left 
				return;
			size_t skipFirst = (*i).Size() / 2;
			size_t count = skipFirst;
			while (skipFirst--) {
				(*i).Push((*i).Pop());
			}
			for (size_t j = 0; j < count; j++) {
				newDesk->Push((*i).Pop());
			}

			return;
		}
	}
}

void Market::tick() {
#define TEST 1

	cashierOperations();
	deskOperations();
#if TEST
	static int c = 0;
	c += 1;
	std::cout << "\tTick count: " << c << std::endl;
	for (size_t i = 0; i < N + 1; i++) {
		std::cout << "\t\tdeck " << i << " : lock(" << lockedForTicks[i] << "), size(" << cashDesks.PeekAt(i).Size() << ")" << std::endl;
	}
#endif
}

void Market::cashierOperations() {

	size_t n = 0;
	for (List<CashDesk>::Iterator i = cashDesks.Begin(); i != cashDesks.End(); ++i, ++n) {
		if ((*i).Size() > 0) {
			
			if (lockedForTicks[n] == 1) {
				(*i).Pop();
				--lockedForTicks[n];
			}
			else if(lockedForTicks[n] == 0){
				Client& client = (*i).Peek();
				lockedForTicks[n] = client.numberOfGoods;
				lockedForTicks[n] += client.creditCard ? 1 : 2;
				//--lockedForTicks[n];
			}
			else {
				--lockedForTicks[n];
			}
		}
	}
}
