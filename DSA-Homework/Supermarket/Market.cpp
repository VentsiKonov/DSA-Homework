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
	ClientState cs;
	
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

	return cs;
}
