#include "Order.h"

#pragma region CONSTRUCTORS & DESTRUCTORS
Order::Order()
{
	this->beverages = nullptr;
	this->beverageNumber = 0;
	this->user = nullptr;
}

Order::Order(User* u)
{
	this->beverages = nullptr;
	this->beverageNumber = 0;
	this->user = u;
}

Order::~Order()
{
	for (int i = 0; i < this->beverageNumber; i++)
	{
		delete this->beverages[i];
	}
	delete[] this->beverages;
}
#pragma endregion