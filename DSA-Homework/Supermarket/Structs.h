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
