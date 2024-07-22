#pragma once
#include "Beverage.h"

#pragma region ENUMS
enum coffeeType
{
	cold,
	hot
};
#pragma endregion

class Coffee : public Beverage
{
private:
	coffeeType type;

public:
	//CONSTRUCTORS & DESTRUCTORS
	Coffee();
	Coffee(coffeeType t, string name, float price);
	~Coffee();

	//SETTERS & GETTERS
	coffeeType getType();
	string getTypeString();

	//PRINTING
	void showBeverage();
	void writeToFile(fstream* f);
	void readFromFile(fstream* f);
};