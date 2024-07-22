#pragma once

#include "Beverage.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;

#define FILENAME "menu.txt"

class Coffee_Shop
{
private: 
	string name;
	Beverage** menu;
	int menuSize;
	fstream menuFile;
	
public:
	//CONSTRUCTORS & DESTRUCTORS
	Coffee_Shop();
	Coffee_Shop(string name);
	~Coffee_Shop();

	//PRINTING
	void welcomePage();
	void showMenu();

	//SELECTION
	void mainPageSelect();

	//MENU MANIPULATION
	void addDrink();
	void addCoffee();
	void addTea();
	void editDrinkPrice();
	void deleteDrink();

	//FILE MANIPULATION
	void writeMenuToFile();
	void readMenuFromFile();
};