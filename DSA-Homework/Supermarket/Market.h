#pragma once

struct Client {
	int ID; // уникален номер на клиента в магазина
	int numberOfGoods; // брой на покупките на клиента
	bool creditCard; // истина ако плаща с крединта карта
};

struct ClientState {
	int CashDeskPosition; // номер на каса
	int QueuePosition; // позиция в опашката на касата
	Client* client;
};

struct MarketState {
	int numberOfCashDesk; // броя на касите които са отворили в момента
	int * numberOfClientsAtCashDecsk; // броя на клиентите на всяка каса в този момент
	int numberOfClientsAtExpressCashDeck;
};


class Market {
public:
	Market(int NumberOfAllCashDecks); // максимални брой каси които може да бъдат отворени в магазина (без експресната)
	void AddClient(Client * clients, int number); // добавяме number клиенти в магазина
	MarketState getMarketState(); // връща състоянието на магазина
	ClientState getClientState(int ID); // връща състоянието на клиента
};