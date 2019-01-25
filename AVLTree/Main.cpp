#include "Tree.h"
#include <random>
#include <time.h>
#include <iostream>

int main() {
	srand(time(NULL));
	Tree t(rand() % 100);
	for (int i = 0; i < 50; i++) {
		t.Insert(rand() % 100);
	}

	t.Draw();

	int k;
	do {
		std::cout << "Delete at: ";
		std::cin >> k;

		t.Delete(k);
		t.Draw();
	} while (k >= 0);

	return 0;
}