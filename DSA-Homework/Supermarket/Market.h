#pragma once

struct Client {
	int ID; // �������� ����� �� ������� � ��������
	int numberOfGoods; // ���� �� ��������� �� �������
	bool creditCard; // ������ ��� ����� � �������� �����
};

struct ClientState {
	int CashDeskPosition; // ����� �� ����
	int QueuePosition; // ������� � �������� �� ������
	Client* client;
};

struct MarketState {
	int numberOfCashDesk; // ���� �� ������ ����� �� �������� � �������
	int * numberOfClientsAtCashDecsk; // ���� �� ��������� �� ����� ���� � ���� ������
	int numberOfClientsAtExpressCashDeck;
};


class Market {
public:
	Market(int NumberOfAllCashDecks); // ���������� ���� ���� ����� ���� �� ����� �������� � �������� (��� �����������)
	void AddClient(Client * clients, int number); // �������� number ������� � ��������
	MarketState getMarketState(); // ����� ����������� �� ��������
	ClientState getClientState(int ID); // ����� ����������� �� �������
};