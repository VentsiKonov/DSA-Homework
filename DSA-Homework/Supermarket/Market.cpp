#include "Market.h"
#include <math.h>
#include <iostream>

#define DEBUG 0

Market::Market(int NumberOfAllCashDecks) : 
// Set constants values
	N(NumberOfAllCashDecks),
	Allow_Rearrange_To_Same_Desk(true),
	Open_Desk_Bound(NumberOfAllCashDecks),
	Close_Desk_Bound(NumberOfAllCashDecks / 10),
	Rearrange_Clients_Bound(NumberOfAllCashDecks / 8)
{
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

void Market::addClient(Client& client, CashDesk* notInDesk) {
	static size_t id = 1;
	if (client.ID == -1)
		client.ID = id++;
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
	CashDesk* skipDesk = Allow_Rearrange_To_Same_Desk ? nullptr : &cashDesk;
	for (size_t i = 0; i < queueSize - skipFirst; i++) {
		addClient(cashDesk.Pop(), skipDesk); // TODO: Assure the client is not in the same desk he is leaving
	}
	
}

bool Market::closeDesk() {
	size_t n = 1;
	for (List<CashDesk>::Iterator i = ++cashDesks.Begin(); i != cashDesks.End(); ++i, ++n) {
		if (lockedForTicks[n] == 0 && (*i).Size() < Close_Desk_Bound) { // Close desk
			rearrangeFrom(*i, 0);
			return true;
		}
	}
	return false;
}

bool Market::openDesk() {
	long iSize = 0;
	for (List<CashDesk>::Iterator i = ++cashDesks.Begin(); i != cashDesks.End(); ++i) {
		iSize = (*i).Size();
		if (iSize > Open_Desk_Bound) {
			CashDesk* newDesk = getFirstClosedDesk();
			if (!newDesk) // No closed desks left 
				return false;
			size_t skipFirst = iSize % 2 == 0 ? iSize / 2 : iSize / 2 + 1;
			size_t count = skipFirst;

			while (skipFirst--) {
				(*i).Push((*i).Pop());
			}
			for (size_t j = 0; j < count; j++) {
				newDesk->Push((*i).Pop());
			}

			return true;
		}
	}
	return false;
}

bool Market::normalizeQueues() {
	long iSize = 0, jSize = 0;
	for (List<CashDesk>::Iterator i = ++cashDesks.Begin(); i != cashDesks.End(); ++i) {
		iSize = (*i).Size();
		if (iSize == 0) // Desk is closed
			continue;

		for (List<CashDesk>::Iterator j = ++List<CashDesk>::Iterator(i); j != cashDesks.End(); ++j) {
			jSize = (*j).Size();
			if (jSize == 0) // Desk is closed
				continue;

			if (abs(iSize - jSize) > Rearrange_Clients_Bound) {
				// For each two queues -> compare sizes and split longer in half
				if (iSize > jSize) {
					rearrangeFrom(*i, iSize % 2 == 0 ? iSize / 2 : iSize / 2 + 1);

				}
				else {
					rearrangeFrom(*j, jSize % 2 == 0 ? jSize / 2 : jSize / 2 + 1);

				}

				return true;
			}
		}
	}

	return false;
}

void Market::deskOperations() {

	return (void)(closeDesk() || normalizeQueues() || openDesk());

}

void Market::tick() {
	cashierOperations();
	deskOperations();

#if DEBUG
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
			} else if (lockedForTicks[n] == 0) {
				Client& client = (*i).Peek();
				lockedForTicks[n] = client.numberOfGoods;
				lockedForTicks[n] += client.creditCard ? 1 : 2;
				--lockedForTicks[n];
			}
			else {
				--lockedForTicks[n];
			}
			
		}
	}
}
