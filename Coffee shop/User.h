#pragma once
#include <string>
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>

using namespace std;

#define BUFFER_SIZE 20

#define CODE_ORDER "1000"
#define CODE_COMPLETED "1001"
#define CODE_EXIT "2000"
#define CODE_REGISTER "3000"
#define CODE_LOGIN "3001"
#define CODE_LOGOUT "3002"
#define CODE_SUCCESS "4000"
#define CODE_ERROR "4001"

class User
{
private:
	int membershipCard;
	int PIN;
	string name;
	float balance;
	int membershipPoints;
	int server;

public:
	//CONSTRUCTORS & DESTRUCTORS
	User();
	User(string name, int balance);
	User(int card, int PIN);
	User(int card, int PIN, string name, float balance, int points);
	~User();

	//SETTERS & GETTERS
	string getName();
	float getBalance();
	void addToBalance(int money);
	void changeName(string name);
	void addPoints(int points);
	void substractPoints(int points);
	void substractFromBalance(int money);

	//PRINTING
	void showInfo();
	void eraseLines(int lines);
	void getMoney();

	//SOCKET MANIPULATION
	void order( int menusize);
	void receiveMenu();
	bool connectToCoffeeShop();
	void account();
	void signin();
	void login();
	void logout();
};