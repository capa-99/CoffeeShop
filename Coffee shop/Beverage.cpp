#include "Beverage.h"

#pragma region CONSTRUCTORS & DESTRUCTORS
Beverage::Beverage()
{
    this->base_price = 0;
    this->cup = small;
    this->name = "";
}

Beverage::Beverage(string name, float price)
{
    this->base_price = price;
    this->cup = small;
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
