#include "User.h"
#include <iomanip>

#pragma region CONSTRUCTORS & DESTRUCTORS
User::User()
{
	this->name = "";
	this->balance = 0;
}

User::User(string name, int balance)
{
	this->name = name;
	this->balance = balance;
}

User::User(int card, int PIN)
{
	this->membershipCard = card;
	this->PIN = PIN;
}

User::User(int card, int PIN, string name, float balance, int points)
{
	this->membershipCard = card;
	this->PIN = PIN;
	this->name = name;
	this->balance = balance;
	this->membershipPoints = points;
}

User::~User()
{
}
#pragma endregion

#pragma region STETTERS & GETTERS
string User::getName()
{
	return this->name;
}

float User::getBalance()
{
	return this->balance;
}

void User::addToBalance(int money)
{
	this->balance = this->balance + money;
}

void User::changeName(string name)
{
	this->name = name;
}

void User::addPoints(int points)
{
	this->membershipPoints = this->membershipPoints + points;
}

void User::substractPoints(int points)
{
	this->addPoints(0 - points);
}

void User::substractFromBalance(int money)
{
	this->addToBalance(0 - money);
}
#pragma endregion

#pragma region PRINTING
void User::showInfo()
{
	cout << left << setw(15) << this->membershipCard << setw(5) << this->PIN << setw(20) << this->name << setw(5) << this->balance << setw(4) << this->membershipPoints << endl;
}
#pragma endregion