#include "Beverage.h"

#pragma region CONSTRUCTORS & DESTRUCTORS
Beverage::Beverage()
{
    this->price = 0;
    this->name = "";
}

Beverage::Beverage(string name, float price)
{
    this->price = price;
    this->name = name;
}

Beverage:: ~Beverage()
{

}

#pragma endregion

#pragma region SETTERS & GETTERS
float Beverage::getPrice()
{
    return this->price;
}

void Beverage::editPrice(float price)
{
    this->price = price;
}

string Beverage::getName()
{
    return this->name;
}
#pragma endregion
