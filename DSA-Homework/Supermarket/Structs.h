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
