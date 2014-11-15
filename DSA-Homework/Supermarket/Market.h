#pragma once

#include "List.h"
#include "Queue.h"
#include "Structs.h"

#define CashDesk Queue<Client>

class Market {
public:
	Market(int NumberOfAllCashDecks); // ���������� ���� ���� ����� ���� �� ����� �������� � �������� (��� �����������)
	void AddClient(Client * clients, int number); // �������� number ������� � ��������
	MarketState getMarketState(); // ����� ����������� �� ��������
	ClientState getClientState(int ID); // ����� ����������� �� �������

	Market(const Market& m);
	Market& operator=(const Market& m);
	~Market();
private:
	// Init in constructor
	bool Allow_Rearrange_To_Same_Desk;
	long Open_Desk_Bound;
	long Close_Desk_Bound;
	long Rearrange_Clients_Bound;
	
	int N;
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

	void copyDataFrom(const Market& m);
};