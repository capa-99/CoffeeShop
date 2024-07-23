#include "User.h"

#pragma region CONSTRUCTORS & DESTRUCTORS
User::User()
{
	this->name = "";
	this->balance = 0;
}

User::User(string name, float balance)
{
	this->name = name;
	this->balance = balance;
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
#pragma endregion

void User::addToBalance()
{
	float cash;
	cout << "Enter desired cash amount" << endl;
	try
	{
		cin >> cash;
		while (cin.fail())
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
			SetConsoleTextAttribute(hConsole, 6);
			cin >> cash;
		}
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
	this->balance = this->balance + cash;
}

#pragma region PRINTING
void User::showInfo()
{
	cout << "Name: " << this->name << endl << "Balace: " << this->balance << endl;
}
#pragma endregion

void User::mainMenu()
{
	while (1)
	{
		int choice;
		cout << "Select an action: " << endl;
		cout << "1. Show info" << endl;
		cout << "2. Edit balance" << endl;
		cout << "3. Enter Coffee Shop" << endl;
		cout << "0. Exit" << endl;
		try
		{
			cin >> choice;
			while (cin.fail() || choice > 3)
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
			this->showInfo();
		}break;
		case 2:
		{
			system("cls");
			this->addToBalance();
		}break;
		case 3:
		{
			system("cls");
			this->connectToCoffeeShop();
		}break;
		case 0:
		{
			return;
		}break;
		default:
		{
			return;
		}
		}
	}
}

#pragma region SOCKET COMMUNICATION
void User::connectToCoffeeShop()
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
		char buffer[20];
		recv(fd, buffer, strlen(buffer), 0);
		cout << "***********************************************************************************************" << endl;
		cout << "                             Welcome to " << buffer << " coffee shop                       " << endl;
		cout << "***********************************************************************************************" << endl;
	}
	else
	{
		cout << "Coffee shop is currently closed" << endl;
	}

	WSACleanup();
}

#pragma endregion