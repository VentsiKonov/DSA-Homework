#include <iostream>
#include <vector>

#include "Market.h"

#define cli(id, goods) {id, goods, false}

using namespace std;
int main() {
	{
		Client* cl = new Client[10];
		for (size_t i = 0; i < 10; i++) {
			cl[i] = cli(i, i%5);
		}

		Market a(5);
		a.AddClient(cl, 10);
		for (size_t i = 0; i < 10; i++) {
			ClientState cs = a.getClientState(i);
			std::cout << cs.CashDeskPosition << " " << cs.QueuePosition << std::endl;
		}
	}
	_CrtDumpMemoryLeaks();
	return 0;
}