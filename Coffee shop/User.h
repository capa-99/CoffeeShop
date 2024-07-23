#pragma once
#include <string>
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>

using namespace std;

class User
{
private:
	string name;
	float balance;

public:
	//CONSTRUCTORS & DESTRUCTORS
	User();
	User(string name, float balance);
	~User();

	//SETTERS & GETTERS
	string getName();
	float getBalance();
	
	//BALANCE
	void addToBalance();

	//PRINTING
	void showInfo();

	void mainMenu();

	//SOCKET COMMUNICATION
	void connectToCoffeeShop();
};