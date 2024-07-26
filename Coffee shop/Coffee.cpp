#include "Coffee.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#pragma region CONSTRUCTORS & DESTRUCTORS
Coffee::Coffee() : Beverage()
{
	this->type = hot;
}

Coffee::Coffee(coffeeType t, string name, float price) : Beverage(name, price)
{
	this->type = t;
}

Coffee::~Coffee()
{

}
#pragma endregion

#pragma region GETTERS & SETTERS
coffeeType Coffee::getType()
{
	return this->type;
}

string Coffee::getTypeString()
{
	if (this->type == cold)
	{
		return "cold";
	}
	if (this->type == hot)
	{
		return "hot";
	}
}
#pragma endregion

#pragma region PRINTING
void Coffee::showBeverage()
{
	cout << left << setw(10) << "Coffee" << setw(20) << this->getName() << setw(8) << this->getPrice() << setw(5) << this->getTypeString() << endl;
}
#pragma endregion

#pragma region FILE MANAGEMENT
void Coffee::writeToFile(fstream* f)
{
	*f << this->getName() << endl << this->getPrice() << endl << this->getType() << endl;
}

void Coffee::readFromFile(fstream* f)
{
	int t;
	*f >> this->name >> this->price >> t;
	this->type = (coffeeType)t;
}
#pragma endregion