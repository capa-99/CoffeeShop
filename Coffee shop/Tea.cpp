#include "Tea.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#pragma region CONSTRUCTORS & DESTRUCTORS
Tea::Tea() : Beverage()
{
	this->type = teabag;
}

Tea::Tea(teaType t, string name, float price) : Beverage(name, price)
{
	this->type = t;
}

Tea::~Tea()
{

}
#pragma endregion

#pragma region GETTERS & SETTERS
teaType Tea::getType()
{
	return this->type;
}

string Tea::getTypeString()
{
	if (this->type == teabag)
	{
		return "teabag";
	}
	if (this->type == looseLeaf)
	{
		return "loose leaf";
	}
}
#pragma endregion

#pragma region PRINTING
void Tea::showBeverage()
{
	cout << left << setw(10) << "Tea" << setw(20) << this->getName() << setw(8) << this->getBasePrice() << setw(5) << this->getTypeString() << endl;
}
#pragma endregion

#pragma region FILE MANAGEMENT
void Tea::writeToFile(fstream* f)
{
	*f << this->getName() << endl << this->getBasePrice() << endl << this->getType() << endl;
}

void Tea::readFromFile(fstream* f)
{
	int t;
	*f >> this->name >> this->base_price >> t;
	this->type = (teaType)t;
}
#pragma endregion