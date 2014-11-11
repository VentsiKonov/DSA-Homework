#include <iostream>

#include "Market.h"

#define cli(id, goods) {id, goods, false}

using namespace std;
int main() {
	{
		Client* cl = new Client[10];
		for (size_t i = 0; i < 10; i++) {
			cl[i] = cli(i, 3);
		}

		Market a(5);
		a.AddClient(cl, 10);
		delete cl;


		for (size_t i = 0; i < 10; i++) {
			ClientState cs = a.getClientState(i);
			std::cout << cs.CashDeskPosition << " " << cs.QueuePosition << std::endl;
		}

		MarketState ms(a.getMarketState());

		std::cout << ms.numberOfCashDesk << endl;
		std::cout << ms.numberOfClientsAtExpressCashDeck << endl;
	}
	_CrtDumpMemoryLeaks();
	return 0;
}