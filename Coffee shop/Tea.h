#pragma once
#include "Beverage.h"

#pragma region ENUMS
enum teaType
{
	teabag,
	looseLeaf
};
#pragma endregion

class Tea : public Beverage
{
private:
	teaType type;

public:
	//CONSTRUCTORS & DESTRUCTORS
	Tea();
	Tea(teaType t, string name, float price);
	~Tea();

	//SETTERS & GETTERS
	teaType getType();
	string getTypeString();

	//PRINTING
	void showBeverage();
	void writeToFile(fstream* f);
	void readFromFile(fstream* f);
};