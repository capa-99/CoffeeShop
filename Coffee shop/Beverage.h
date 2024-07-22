#pragma once
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

#pragma region ENUMS
//enums that make it easier to work with different integers

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
    small,
    medium,
    large
};

#pragma endregion

class Beverage
{
protected:
    float base_price;
    vector<topping> toppings;
    cupSize cup;
    string name;

public:
    //CONSTRUCTORS & DESTRUCTORS
    Beverage();
    Beverage(string name, float price);
    ~Beverage();

    //SETTERS & GETTERS
    float getBasePrice();
    float getPrice();
    string getName();
    void addSize(cupSize ss);

    //TOPPING MANIPULATION
    void addTopping(topping t);
    void editPrice(float price);

    //PRINTING
    void virtual showBeverage() = 0;
    void virtual writeToFile(fstream* f) = 0;
    void virtual readFromFile(fstream* f) = 0;
};