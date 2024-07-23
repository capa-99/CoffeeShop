#pragma once
#include "Beverage.h"
#include "User.h"

class Order
{
private:
	Beverage** beverages;
	int beverageNumber;
	User* user;


public:
	//CONSTRUCTORS & DESTRUCTORS
	Order();
	Order(User* u);
	~Order();
};