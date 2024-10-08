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
#define CODE_EXIT "2000"

class User
{
private:
	int membershipCard;
	int PIN;
	string name;
	float balance;
	int membershipPoints;

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
};