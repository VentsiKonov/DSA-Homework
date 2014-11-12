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
	// Init in constructor
	const bool Allow_Rearrange_To_Same_Desk;
	const long Open_Desk_Bound;
	const long Close_Desk_Bound;
	const long Rearrange_Clients_Bound;
	
	const int N;
	List<CashDesk> cashDesks;
	int* lockedForTicks;
	size_t ids;

	void tick();
	void deskOperations();
	void cashierOperations();
	CashDesk& getSmallestOpenDesk(CashDesk* differentFrom = nullptr);
	CashDesk* getFirstClosedDesk();
	void addClient(Client& client, CashDesk* notInDesk = nullptr);
	void rearrangeFrom(CashDesk& desk, size_t number);
	bool closeDesk();
	bool openDesk();
	bool normalizeQueues();

};