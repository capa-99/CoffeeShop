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

string Order::getCupSizeString()
{
	if (this->cup == smaller)
	{
		return "small";
	}
	if (this->cup == medium)
	{
		return "medium";
	}
	if (this->cup == large)
	{
		return "large";
	}
}

string Order::getAllToppingString()
{
	string ret = "";
	for (int i = 0; i < this->toppings.size(); i++)
	{
		switch(this->toppings[i])
		{
		case milk:
		{
			ret = ret + "milk ";
		}break;
		case sugar:
		{
			ret = ret + "sugar ";
		}break;
		case vanilla:
		{
			ret = ret + "vanilla ";
		}break;
		case caramel:
		{
			ret = ret + "caramel ";
		}break;
		case whipped_cream:
		{
			ret = ret + "whipped_cream ";
		}break;
		case cinnamon:
		{
			ret = ret + "cinnamon ";
		}break;
		case cocoa:
		{
			ret = ret + "cocoa ";
		}break;
		case chocolate:
		{
			ret = ret + "chocolate ";
		}break;
		case fruit:
		{
			ret = ret + "fruit ";
		}break;
		}
	}
	return ret;
}
#pragma endregion

#pragma region PRINTNG
void Order::showOrder()
{
	cout << left << setw(20) << this->drink->getName() << setw(12) << this->getCupSizeString() << setw(50) << this->getAllToppingString() << setw(8) << this->orderPrice << setw(10) << "this->user->getName()" << endl;
}
#pragma endregion