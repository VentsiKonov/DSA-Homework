#include "Market.h"

Market::Market(int NumberOfAllCashDecks) : N(NumberOfAllCashDecks){
	if (NumberOfAllCashDecks < 1)
		throw "You cannot have less than 1 cash deck!";

	// Init
	for (int i = 0; i < NumberOfAllCashDecks; ++i) {
		Queue<Client> j;
		cashDesks.PushBack(j);
	}
}

MarketState Market::getMarketState() {
	MarketState ms;
	ms.numberOfCashDesk = 0;
	ms.numberOfClientsAtCashDecsk = new int[N]; // The caller of this method should delete this
	ms.numberOfClientsAtExpressCashDeck = expressDesk.Size();
	int n = 0;
	for (List<CashDesk>::Iterator it = cashDesks.Begin(); it != cashDesks.End(); ++it, ++n) {
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

	if (cs.client == nullptr) { // Client cannot be found in the ordinary decks
		currentDeskClients = expressDesk.Size();
		for (size_t i = 0; i < currentDeskClients; i++) {
			currentClient = &expressDesk.Pop();

			if (currentClient->ID == ID) {
				cs.CashDeskPosition = -1; // Express deck number??
				cs.QueuePosition = i;
				cs.client = currentClient;
			}

			expressDesk.Push(*currentClient);
		}
	}

	return cs;
}

void Market::AddClient(Client* clients, int number) {

	for (int i = 0; i < number; i++) {
		if (clients[i].numberOfGoods > 0) {
			if (clients[i].numberOfGoods <= 3 && expressDesk.Size() < 2 * N)
				expressDesk.Push(clients[i]);
			else
				getSmallestDesk().Push(clients[i]);
		}
	}

	Tick();
}

CashDesk& Market::getSmallestDesk() {
	size_t currentSmallest = 0;
	CashDesk * smallestDesk = &cashDesks.PeekFront();
	for (List<CashDesk>::Iterator i = cashDesks.Begin(); i != cashDesks.End(); ++i) {
		if ((*i).Size() != 0) {
			if (currentSmallest == 0 || currentSmallest > (*i).Size()) {
				currentSmallest = (*i).Size();
				smallestDesk = &*i;
			}
		}
	}
	
	return *smallestDesk;
}

void Market::Tick() {

}
