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