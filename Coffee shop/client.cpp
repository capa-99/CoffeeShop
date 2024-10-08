#pragma once
#include <string>
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>
#include <iomanip>
#include "User.h"

using namespace std;

#define BUFFER_SIZE 20

#define CODE_ORDER "1000"
#define CODE_EXIT "2000"
#define CODE_REGISTER "3000"
#define CODE_LOGIN "3001"

User* u;

void order(int fd, int menusize);
void receiveMenu(int fd);
void connectToCoffeeShop();
void account(int fd);
void signin(int fd);
void login(int fd);

#pragma region "FUNCTION DEFINITIONS"
void connectToCoffeeShop()
{
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		printf("WSAStartup failed: %d\n", result);
	}

	int fd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	address.sin_port = htons(2000);
	address.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &address.sin_addr.s_addr);

	result = connect(fd, (struct sockaddr*)&address, sizeof(address));

	if (result == 0)
	{
		account(fd);
	}
	else
	{
		cout << "Coffee shop is currently closed" << endl;
	}
	closesocket(fd);
	WSACleanup();
}

void account(int fd)
{
		int choice;
		cout << "Select an action: " << endl;
		cout << "1. Register" << endl;
		cout << "2. Login" << endl;
		cout << "0. Exit" << endl;
		try
		{
			cin >> choice;
			while (cin.fail() || choice > 2)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 4);
				if (cin.fail())
				{
					cin.clear();
					char c;
					while (cin.get(c) && c != '\n') {}
					cerr << "Please enter a number" << endl;
				}
				else
				{
					cerr << "Please enter a valid number" << endl;
				}
				SetConsoleTextAttribute(hConsole, 6);
				cin >> choice;
			}
		}
		catch (runtime_error& e)
		{
			cerr << e.what() << endl;
		}

		switch (choice)
		{
		case 1:
		{
			system("cls");
			signin(fd);
		}break;
		case 2:
		{
			system("cls");
			login(fd);
		}break;
		case 0:
		{
			//strcpy(buffer, CODE_EXIT);
			//send(fd, buffer, 20, 0);
			return;
		}break;
		default:
		{
			return;
		}
		}

}

void signin(int fd)
{
	string name;
	cout << "Name: ";
	cin >> name;
	int balance;
	cout << "Balance: ";
	cin >> balance;
	u = new User(name, balance);
	char buffer[20];
	strcpy(buffer, CODE_REGISTER);
	send(fd, buffer, 20, 0);
	strcpy(buffer, name.c_str());
	send(fd, buffer, 20, 0);
	string message;
	message = to_string(balance);
	strcpy(buffer, message.c_str());
	send(fd, buffer, 20, 0);

	//receive
}

void login(int fd)
{
	int card;
	cout << "Card number: ";
	cin >> card;
	int pin;
	cout << "PIN: ";
	cin >> pin;
	//.....send to server and receive the rest of data if succesful
	u = new User(card, pin);
}

void receiveMenu(int fd)
{
	char buffer[20];
	int recvSize = recv(fd, buffer, 20, 0);
	cout << "***********************************************************************************************" << endl;
	cout << "                             Welcome to " << buffer << " coffee shop                       " << endl;
	cout << "***********************************************************************************************" << endl;
	cout << "~~~~~~~~~~ MENU ~~~~~~~~~~" << endl;
	cout << left << setw(8) << "Number: " << setw(10) << "Beverage: " << setw(20) << "Name: " << setw(8) << "Price : " << setw(8) << "Type: " << endl;
	int menuSize;
	recvSize = recv(fd, buffer, 20, 0);
	menuSize = atoi(buffer);
	for (int i = 0; i < menuSize; i++)
	{
		cout << left << setw(8) << (i + 1);
		recvSize = recv(fd, buffer, 20, 0);
		cout << left << setw(10) << buffer;
		recvSize = recv(fd, buffer, 20, 0);
		cout << left << setw(20) << buffer;
		recvSize = recv(fd, buffer, 20, 0);
		cout << left << setw(8) << buffer;
		recvSize = recv(fd, buffer, 20, 0);
		cout << left << setw(5) << buffer << endl;
	}


	while (1)
	{
		int choice;
		cout << "Select an action: " << endl;
		cout << "1. Order" << endl;
		cout << "0. Exit" << endl;
		try
		{
			cin >> choice;
			while (cin.fail() || choice > 1)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 4);
				if (cin.fail())
				{
					cin.clear();
					char c;
					while (cin.get(c) && c != '\n') {}
					cerr << "Please enter a number" << endl;
				}
				else
				{
					cerr << "Please enter a valid number" << endl;
				}
				SetConsoleTextAttribute(hConsole, 6);
				cin >> choice;
			}
		}
		catch (runtime_error& e)
		{
			cerr << e.what() << endl;
		}

		switch (choice)
		{
		case 1:
		{
			system("cls");
			order(fd, menuSize);
		}break;
		case 0:
		{
			strcpy(buffer, CODE_EXIT);
			send(fd, buffer, 20, 0);
			return;
		}break;
		default:
		{
			return;
		}
		}
	}
}

void order(int fd, int menuSize)
{
	char buffer[20];
	strcpy(buffer, CODE_ORDER);
	send(fd, buffer, 20, 0);
	int drink;
	cout << "Select the drink you want to order: ";
	try
	{
		cin >> drink;
		while (cin.fail() || drink > menuSize || drink < 1)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 4);
			if (cin.fail())
			{
				cin.clear();
				char c;
				while (cin.get(c) && c != '\n') {}
				cerr << "Please enter a number" << endl;
			}
			else
			{
				cerr << "Please enter a valid number" << endl;
			}
			SetConsoleTextAttribute(hConsole, 6);
			cin >> drink;
		}
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
	string message;
	message = to_string(drink - 1);
	strcpy(buffer, message.c_str());
	send(fd, buffer, 20, 0);
	int cup;
	cout << "Choose the cup size of the drink: " << endl << "1. small, 2. medium, 3. large" << endl;
	try
	{
		cin >> cup;
		while (cin.fail() || cup > 3)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 4);
			if (cin.fail())
			{
				cin.clear();
				char c;
				while (cin.get(c) && c != '\n') {}
				cerr << "Please enter a number" << endl;
			}
			else
			{
				cerr << "Please enter a valid number" << endl;
			}
			SetConsoleTextAttribute(hConsole, 6);
			cin >> cup;
		}
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
	message = to_string(cup - 1);
	strcpy(buffer, message.c_str());
	send(fd, buffer, 20, 0);
	int toppNum = 0;
	int toppings = 0;
	int topp;
	int yes = 1;
	while (yes)
	{
		cout << "Choose wich toppings you want: " << endl;
		cout << "1. Milk" << endl;
		cout << "2. Sugar" << endl;
		cout << "3. Vanilla" << endl;
		cout << "4. Caramel" << endl;
		cout << "5. Whipped cream" << endl;
		cout << "6. Cinnamon" << endl;
		cout << "7. Cococa" << endl;
		cout << "8. Chocolate" << endl;
		cout << "9. Fruit" << endl;
		cout << "0. Exit" << endl;
		try
		{
			cin >> topp;
			while (cin.fail() || topp > 9)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 4);
				if (cin.fail())
				{
					cin.clear();
					char c;
					while (cin.get(c) && c != '\n') {}
					cerr << "Please enter a number" << endl;
				}
				else
				{
					cerr << "Please enter a valid number" << endl;
				}
				SetConsoleTextAttribute(hConsole, 6);
				cin >> topp;
			}
		}
		catch (runtime_error& e)
		{
			cerr << e.what() << endl;
		}

		switch (topp)
		{
		case 0:
		{
			yes = 0;
		}break;
		default:
		{
			toppNum++;
			toppings = toppings * 10 + topp - 1;
		}
		}
	}
	message = to_string(toppings);
	strcpy(buffer, message.c_str());
	send(fd, buffer, 20, 0);
}
#pragma endregion

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 6);

	connectToCoffeeShop();

	return 0;
}