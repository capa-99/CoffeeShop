#include "Coffe Shop.h"

int main()
{
	Coffee_Shop* c = new Coffee_Shop("NOKI");
	c->readMenuFromFile();
	c->configureServer();
	c->welcomePage();
	c->mainPageSelect();
	

	return 0;
}