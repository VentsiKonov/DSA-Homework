#pragma once

#include "List.h"
#include "Queue.h"
#include "Structs.h"

#define CashDeck Queue<Client>

class Market {
public:
	Market(int NumberOfAllCashDecks); // ���������� ���� ���� ����� ���� �� ����� �������� � �������� (��� �����������)
	void AddClient(Client * clients, int number); // �������� number ������� � ��������
	MarketState getMarketState(); // ����� ����������� �� ��������
	ClientState getClientState(int ID); // ����� ����������� �� �������

private:
	const int N;
	List<CashDeck> cashDecks;
	CashDeck expressDeck;
};