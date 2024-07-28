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

#define CODE_ORDER "1000"
#define CODE_EXIT "2000"

class Coffee_Shop
{
private: 
	string name;
	Beverage** menu;
	int menuSize;
	fstream menuFile;
	Order** pendingOrders;
	int orderNumber;
	int serverFD;
	
public:
	//CONSTRUCTORS & DESTRUCTORS
	Coffee_Shop();
	Coffee_Shop(string name);
	~Coffee_Shop();

	//PRINTING
	void welcomePage();
	void showMenu();
	void showOrders();

	//SELECTION
	void mainPageSelect();

	//MENU MANIPULATION
	void addDrink();
	void addCoffee();
	void addTea();
	void editDrinkPrice();
	void deleteDrink();

	//ORDER MANIPULATION
	void addOrder(Order* o);

	//FILE MANIPULATION
	void writeMenuToFile();
	void readMenuFromFile();

	//SOCKET COMMUNICATION
	void configureServer();
	static DWORD WINAPI acceptClients(LPVOID p);
};