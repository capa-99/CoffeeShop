#include "User.h"
#include <iomanip>

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
		int recvSize = recv(fd, buffer, 20, 0);
		cout << "***********************************************************************************************" << endl;
		cout << "                             Welcome to " << buffer << " coffee shop                       " << endl;
		cout << "***********************************************************************************************" << endl;
		cout << "~~~~~~~~~~ MENU ~~~~~~~~~~" << endl;
		cout << left << setw(8) << "Number: " << setw(10) << "Beverage: " << setw(20) << "Name: " << setw(8) << "Price : " << setw(8) << "Type: " << endl;
		int menuSize;
		recvSize = recv(fd, buffer,20, 0);
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
				this->order(fd, menuSize);
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
	else
	{
		cout << "Coffee shop is currently closed" << endl;
	}
	closesocket(fd);
	WSACleanup();
}

void User::order(int fd, int menuSize)
{
	char buffer[20];
	strcpy(buffer, CODE_ORDER);
	send(fd, buffer, 20, 0);
	int drink;
	cout << "Select the drink you want to order: ";
	try
	{
		cin >> drink;
		while (cin.fail() || drink > menuSize)
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
	cout << "Choose the cup size of the drink: " << endl << "1. small, 2. medium, 3. large" <<endl;
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
	while (1)
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
			return;
		}break;
		default:
		{
			toppNum++;
			toppings = toppings * 10 + topp;
		}
		}
	}
	message = to_string(toppings);
	strcpy(buffer, message.c_str());
	send(fd, buffer, 20, 0);
}
#pragma endregion