#include "Market.h"

Market::Market(int NumberOfAllCashDecks) : N(NumberOfAllCashDecks){
	if (NumberOfAllCashDecks < 1)
		throw "You cannot have less than 1 cash deck!";

	// Init
	for (size_t i = 0; i < NumberOfAllCashDecks; ++i) {
		Queue<Client> j;
		cashDecks.PushBack(j);
	}
}

MarketState Market::getMarketState() {
	MarketState ms;
	ms.numberOfCashDesk = 0;
	ms.numberOfClientsAtCashDecsk = new int[N]; // The caller of this method should delete this
	ms.numberOfClientsAtExpressCashDeck = expressDeck.Size();
	int n = 0;
	for (List<CashDeck>::Iterator it = cashDecks.Begin(); it != cashDecks.End(); ++it, ++n) {
		ms.numberOfClientsAtCashDecsk[n] = (*it).Size();
		
		if (ms.numberOfClientsAtCashDecsk[n] != 0)
			++ms.numberOfCashDesk;

	}

	return ms;

}

ClientState Market::getClientState(int ID) {
	ClientState cs{ 0, 0, nullptr };
	
	size_t currentDeckClients = 0;
	Client* currentClient;
	int n = 0;
	for (List<CashDeck>::Iterator it = cashDecks.Begin(); it != cashDecks.End(); ++it, ++n) {
		currentDeckClients = (*it).Size();
		
		if (currentDeckClients > 0)
			for (size_t pos = 0; pos < currentDeckClients; pos++) {
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
		currentDeckClients = expressDeck.Size();
		for (size_t i = 0; i < currentDeckClients; i++) {
			currentClient = &expressDeck.Pop();

			if (currentClient->ID == ID) {
				cs.CashDeskPosition = -1; // Express deck number??
				cs.QueuePosition = i;
				cs.client = currentClient;
			}

			expressDeck.Push(*currentClient);
		}
	}

	return cs;
}

void Market::AddClient(Client* clients, int number) {

	for (size_t i = 0; i < number; i++) {
		if (clients[i].numberOfGoods > 0) {
			if (clients[i].numberOfGoods <= 3 && expressDeck.Size() < 2 * N)
				expressDeck.Push(clients[i]);
			else
				cashDecks.PeekAt(getSmallestDeckNumber()).Push(clients[i]);
		}
	}

	Tick();
}

size_t Market::getSmallestDeckNumber() {
	int currentSmallest = 0;
	int smallestDeckNumber = 0;
	int n = 0;
	for (List<CashDeck>::Iterator i = cashDecks.Begin(); i != cashDecks.End(); ++i, ++n) {
		if ((*i).Size() != 0) {
			if (currentSmallest == 0 || currentSmallest > (*i).Size()) {
				currentSmallest = (*i).Size();
				smallestDeckNumber = n;
			}
		}
	}
	
	return smallestDeckNumber;
}

void Market::Tick() {

}
