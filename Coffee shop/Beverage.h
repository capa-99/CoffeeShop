#pragma once
#include <string>
#include <stdio.h>

using namespace std;

class Beverage
{
protected:
    float price;
    string name;

public:
    //CONSTRUCTORS & DESTRUCTORS
    Beverage();
    Beverage(string name, float price);
    ~Beverage();

    //SETTERS & GETTERS
    float getPrice();
    string getName();
    string virtual getTypeString() = 0;
    void editPrice(float price);

    //PRINTING
    void virtual showBeverage() = 0;
    void virtual writeToFile(fstream* f) = 0;
    void virtual readFromFile(fstream* f) = 0;
};