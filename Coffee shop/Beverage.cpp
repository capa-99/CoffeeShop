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
float Beverage::getBasePrice()
{
    return this->base_price;
}

float Beverage::getPrice()
{
    float price = this->base_price;
    price = price + this->toppings.size() * 5;
    if (this->cup == small)
    {
        return price;
    }
    if (this->cup == medium)
    {
        return price * 1.5;
    }
    if (this->cup == large)
    {
        return price * 2;
    }
}

string Beverage::getName()
{
    return this->name;
}

void Beverage::addSize(cupSize ss)
{
    this->cup = ss;
}
#pragma endregion

#pragma region TOPPING MANIPULATION
void Beverage::addTopping(topping t)
{
    this->toppings.push_back(t);
}

void Beverage::editPrice(float price)
{
    this->base_price = price;
}
#pragma endregion 
