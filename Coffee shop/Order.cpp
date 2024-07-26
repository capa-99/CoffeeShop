#include "Order.h"

#pragma region CONSTRUCTORS & DESTRUCTORS
Order::Order()
{
	this->user = nullptr;
	this->orderPrice = 0
}

Order::Order(float price)
{
	this->user = nullptr;
	this->base_price = price;
}

Order::Order(User* u, float price)
{
	this->user = u;
	this->base_price = price;
}

Order::~Order()
{

}
#pragma endregion