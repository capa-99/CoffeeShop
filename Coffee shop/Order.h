#pragma once
#include "User.h"
#include <vector>

#pragma region ENUMS
enum topping
{
    milk,
    sugar,
    vanilla,
    caramel,
    whipped_cream,
    cinnamon,
    cocoa,
    chocolate,
    fruit
};

enum cupSize
{
    smaller,
    medium,
    large
};
#pragma endregion

class Order
{
private:
    cupSize cup;
    vector<topping> toppings;
    float base_price;
	float orderPrice;
	User* user;


public:
	//CONSTRUCTORS & DESTRUCTORS
	Order();
	Order(float baseprice);
	Order(User* u, float price);
	~Order();

};