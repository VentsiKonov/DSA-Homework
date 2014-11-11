#include <iostream>

#include "Market.h"

#define cli(id, goods) {id, goods, false}

using namespace std;
int main() {
	{
		Client* cl = new Client[10];
		for (size_t i = 0; i < 10; i++) {
			cl[i] = cli(i, 4);
		}

		Market a(3);
		a.AddClient(cl, 10);
		delete cl;
		for (size_t j = 0; j < 5; j++) {
			for (size_t i = 0; i < 10; i++) {
				ClientState cs = a.getClientState(i);
				std::cout << cs.client->ID << " " << cs.CashDeskPosition << " " << cs.QueuePosition << std::endl;
			}
			a.AddClient(nullptr, 0);
		}
		

		MarketState ms(a.getMarketState());

		std::cout << ms.numberOfCashDesk << endl;
		std::cout << ms.numberOfClientsAtExpressCashDeck << endl;
		delete ms.numberOfClientsAtCashDecsk;
	}
	_CrtDumpMemoryLeaks();
	return 0;
}