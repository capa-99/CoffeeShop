#include "Order.h"

#pragma region CONSTRUCTORS & DESTRUCTORS
Order::Order()
{
	this->user = nullptr;
	this->orderPrice = 0;
	this->cup = smaller;
	this->drink = nullptr;
}

Order::Order(Beverage* b)
{
	this->user = nullptr;
	this->drink = b;
	this->cup = smaller;
}

Order::Order(User* u, Beverage* b)
{
	this->user = u;
	this->drink = b;
	this->cup = smaller;
}

Order::~Order()
{

}
#pragma endregion

#pragma region GETTERS & SETTERS
void Order::addCupSize(cupSize c)
{
	this->cup = c;
}

void Order::addTopping(topping t)
{
	this->toppings.push_back(t);
}

void Order::calculatePrice()
{
	this->orderPrice = (this->drink->getPrice() + 5 * this->toppings.size()) * (this->cup + 0.5);
}
#pragma endregion

#pragma region PRINTNG
void Order::showOrder()
{
	cout << left << setw(20) << this->drink->getName() << setw(12) << "Cup size: " << setw(50) << "Toppings: " << setw(8) << this->orderPrice << setw(10) << "this->user->getName()" << endl;
}
#pragma endregion