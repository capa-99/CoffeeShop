#pragma once
#include "Beverage.h"
#include "User.h"
#include <vector>
#include <iomanip>

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
    Beverage* drink;
    cupSize cup;
    vector<topping> toppings;
	float orderPrice;
	User* user;


public:
	//CONSTRUCTORS & DESTRUCTORS
	Order();
	Order(Beverage* b);
	Order(User* u, Beverage* b);
	~Order();

    //GETTERS & SETTERS
    void addCupSize(cupSize c);
    void addTopping(topping t);
    void calculatePrice();

    //PRINTING
    void showOrder();
};