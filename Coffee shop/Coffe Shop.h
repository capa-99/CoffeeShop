#pragma once
#include "Beverage.h"
#include "Order.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define FILENAME "menu.txt"

class Coffee_Shop
{
private: 
	string name;
	Beverage** menu;
	int menuSize;
	fstream menuFile;
	Order** pendingOrders;
	int orderNumber;
	
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

	//SOCKET COMMUNICATION
	void configureServer();
};