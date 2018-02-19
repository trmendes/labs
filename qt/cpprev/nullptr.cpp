#include "nullptr.h"

int Teste::func(int a) {
	return 0;
}

int Teste::func(int *a) {
	return 0;
}

int main(void) {
	Teste *t = new Teste();
	t->func(nullptr);
}
