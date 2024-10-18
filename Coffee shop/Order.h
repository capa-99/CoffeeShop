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
	int user;
    int userAddress;


public:
	//CONSTRUCTORS & DESTRUCTORS
	Order();
	Order(Beverage* b, int user);
	~Order();

    //GETTERS & SETTERS
    void addCupSize(cupSize c);
    void addTopping(topping t);
    void calculatePrice();
    string getCupSizeString();
    string getAllToppingString();
    int getPrice();
    void setAddress(int addr);
    int getAddress();

    //PRINTING
    void showOrder();
};