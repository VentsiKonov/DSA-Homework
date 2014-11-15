#include "Market.h"

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
	for (int i = 0; i < N + 1; ++i) {
		Queue<Client> j;
		cashDesks.PushBack(j);
		lockedForTicks[i] = 0;
	}

	ids = 1;
	
}

Market::~Market() {
	delete[] lockedForTicks;
}

MarketState Market::getMarketState() {
	MarketState ms;
	ms.numberOfCashDesk = 0;
	ms.numberOfClientsAtCashDecsk = new int[N]; // The caller of this method should delete this
	ms.numberOfClientsAtExpressCashDeck = cashDesks.Front().Size();

	int n = 0;
	List<CashDesk>::Iterator end = cashDesks.End();
	for (List<CashDesk>::Iterator it = ++cashDesks.Begin(); it != end; ++it, ++n) {
		ms.numberOfClientsAtCashDecsk[n] = (int)(*it).Size();
		
		if (ms.numberOfClientsAtCashDecsk[n] > 0)
			++ms.numberOfCashDesk;

	}
	
	return ms;

}

ClientState Market::getClientState(int ID) {

	ClientState cs{ 0, 0, nullptr };
	
	size_t currentDeskClients = 0;
	Client* currentClient = nullptr;
	int n = 0;
	List<CashDesk>::Iterator end = cashDesks.End();
	for (List<CashDesk>::Iterator it = cashDesks.Begin(); it != end; ++it, ++n) {
		currentDeskClients = (*it).Size();
		
		if (currentDeskClients > 0)
			for (size_t pos = 0; pos < currentDeskClients; pos++) {
				currentClient = &(*it).Pop();

				if (currentClient->ID == ID) {
					cs.CashDeskPosition = n;
					cs.QueuePosition = pos;
					cs.client = new Client(*currentClient); //currentClient;
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
	size_t iSize = 0;
	List<CashDesk>::Iterator end = cashDesks.End();
	while (i != end) {
		if (differentFrom && &(*i) == differentFrom) {
			++i;
			continue;
		}

		iSize = (*i).Size();
		if (iSize != 0) {
			if (currentSmallest == 0 || currentSmallest > iSize) {
				currentSmallest = iSize;
				smallestDesk = &*i;
			}
		}
		++i;
	}
	
	return *smallestDesk;
}

CashDesk* Market::getFirstClosedDesk() {
	List<CashDesk>::Iterator end = cashDesks.End();
	for (List<CashDesk>::Iterator i = ++cashDesks.Begin(); i != end; ++i) {
		if ((*i).Size() == 0) 
			return &*i;
	}

	return nullptr; // No closed desks left
}

void Market::addClient(Client& client, CashDesk* notInDesk) {
	if (client.ID < 1)
		client.ID = ids++;

	if (client.numberOfGoods > 0) {
		if (client.numberOfGoods <= 3 && cashDesks.Front().Size() < 2 * N) {
			cashDesks.Front().Push(client);
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
	List<CashDesk>::Iterator end = cashDesks.End();
	for (List<CashDesk>::Iterator i = ++cashDesks.Begin(); i != end; ++i, ++n) {
		if (lockedForTicks[n] == 0 && (*i).Size() < Close_Desk_Bound) { // Close desk
			rearrangeFrom(*i, 0);
			return true;
		}
	}
	return false;
}

bool Market::openDesk() {
	long iSize = 0;
	List<CashDesk>::Iterator end = cashDesks.End();
	for (List<CashDesk>::Iterator i = ++cashDesks.Begin(); i != end; ++i) {
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
	if (N < 2)
		return false;

	long iSize = 0, jSize = 0, difference = 0;
	List<CashDesk>::Iterator end = cashDesks.End();
	List<CashDesk>::Iterator j(nullptr);
	for (List<CashDesk>::Iterator i = ++cashDesks.Begin(); i != end; ++i) {
		iSize = (*i).Size();
		if (iSize == 0) // Desk is closed
			continue;

		for (j = i, j++; j != end; ++j) {
			jSize = (*j).Size();
			if (jSize == 0) // Desk is closed
				continue;

			difference = (iSize - jSize > 0) ? iSize - jSize : jSize - iSize;
			if (difference > Rearrange_Clients_Bound) {
				// For each two queues -> compare sizes and split longer in half
				if (iSize > jSize) {
					rearrangeFrom(*i, iSize % 2 == 0 ? iSize / 2 : iSize / 2 + 1);

				}
				else {
					rearrangeFrom(*j, jSize % 2 == 0 ? jSize / 2 : jSize / 2 + 1);

				}

				return true;
			}
		} // Inner for
	}

	return false;
}

void Market::deskOperations() {

	return (void)(closeDesk() || normalizeQueues() || openDesk());

}

void Market::tick() {

	cashierOperations();
	deskOperations();
}

void Market::cashierOperations() {

	size_t n = 0;
	List<CashDesk>::Iterator end = cashDesks.End();
	for (List<CashDesk>::Iterator i = cashDesks.Begin(); i != end; ++i, ++n) {
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
