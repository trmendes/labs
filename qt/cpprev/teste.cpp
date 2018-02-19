#include <iostream>

#include "teste.h"

using namespace std;

auto base::metodo_2() -> int {
	return 0;
}

int base::metodo_1() {
	return 0;
}

int heranca::metodo_1() {
	return 1;
}

auto heranca::metodo_2() -> int {
	return 1;
}

int main(void) {
	heranca * h = new heranca();
	cout << h->metodo_2() << endl;
	cout << h->metodo_1() << endl;
	return 0;
}
