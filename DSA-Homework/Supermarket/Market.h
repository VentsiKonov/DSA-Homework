#pragma once

#include "List.h"
#include "Queue.h"
#include "Structs.h"

#define CashDeck Queue<Client>

class Market {
public:
	Market(int NumberOfAllCashDecks); // максимални брой каси които може да бъдат отворени в магазина (без експресната)
	void AddClient(Client * clients, int number); // добавяме number клиенти в магазина
	MarketState getMarketState(); // връща състоянието на магазина
	ClientState getClientState(int ID); // връща състоянието на клиента

private:
	const int N;
	List<CashDeck> cashDecks;
	CashDeck expressDeck;
};