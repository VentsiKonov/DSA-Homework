#pragma once

#include "List.h"
#include "Queue.h"
#include "Structs.h"

#define CashDesk Queue<Client>

class Market {
public:
	Market(int NumberOfAllCashDecks); // максимални брой каси които може да бъдат отворени в магазина (без експресната)
	void AddClient(Client * clients, int number); // добавяме number клиенти в магазина
	MarketState getMarketState(); // връща състоянието на магазина
	ClientState getClientState(int ID); // връща състоянието на клиента

	~Market();
private:
	const int N;
	List<CashDesk> cashDesks;
	bool* locked;

	void tick();
	void deskOperations();
	CashDesk& getSmallestOpenDesk(CashDesk* differentFrom = nullptr);
	CashDesk* getFirstClosedDesk();
	void addClient(const Client& client, CashDesk* notInDesk = nullptr);
	void rearrangeFrom(CashDesk& desk, size_t number);

};