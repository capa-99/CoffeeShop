#include "Coffe Shop.h"
#include "Coffee.h"
#include "Tea.h"
#include <windows.h>
#include <iostream>
#include <typeinfo>

#pragma region CONSTRUCTORS & DESTRUCTORS
Coffee_Shop::Coffee_Shop()
{
	this->name = "";
	this->menuSize = 0;
	this->menu = nullptr;
	this->pendingOrders = nullptr;
	this->orderNumber = 0;
}

Coffee_Shop::Coffee_Shop(string name)
{
	this->name = name;
	this->menuSize = 0;
	this->menu = nullptr;
	this->pendingOrders = nullptr;
	this->orderNumber = 0;
}

Coffee_Shop::~Coffee_Shop()
{
	for (int i = 0; i < this->menuSize; i++)
	{
		delete this->menu[i];
	}
	delete[] menu;

	for (int i = 0; i < this->orderNumber; i++)
	{
		delete this->pendingOrders[i];
	}
	delete[] this->pendingOrders;
}
#pragma endregion

#pragma region PRINTING
void Coffee_Shop::welcomePage()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	cout << "***********************************************************************************************" << endl;
	cout << "                             Welcome to " << this->name << " coffee shop                       " << endl;
	cout << "***********************************************************************************************" << endl;
}

void Coffee_Shop::showMenu()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	cout << "~~~~~~~~~~ MENU ~~~~~~~~~~" << endl;
	cout << left << setw(8) << "Number: " << setw(10) << "Beverage: " << setw(20) <<  "Name: " << setw(8) << "Price : "  << setw(8) << "Type: " << endl;
	SetConsoleTextAttribute(hConsole, 14);
	for (int i = 0; i < this->menuSize; i++)
	{
		cout <<left << setw(8) << (i+1);
		this->menu[i]->showBeverage();
	}
}
#pragma endregion

#pragma region SELECTION
void Coffee_Shop::mainPageSelect()
{
	while (1)
	{
		int choice;
		cout << "Select an action: " << endl;
		cout << "1. Add drink to the menu" << endl;
		cout << "2. Manage drink prices on the menu" << endl;
		cout << "3. Remove drink from the menu" << endl;
		cout << "4. Show the menu" << endl;
		cout << "0. Exit" << endl;
		try
		{
			cin >> choice;
			while(cin.fail() || choice > 4)
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
				SetConsoleTextAttribute(hConsole, 14);
				cin >> choice;
			}
		}
		catch(runtime_error &e)
		{
			cerr << e.what() << endl;
		}
		
		switch (choice)
		{
		case 1:
		{
			system("cls");
			this->welcomePage();
			this->addDrink();
		}break;
		case 2:
		{
			system("cls");
			this->welcomePage();
			this->showMenu();
			this->editDrinkPrice();
		}break;
		case 3:
		{
			system("cls");
			this->welcomePage();
			this->showMenu();
			this->deleteDrink();
		}break;
		case 4:
		{
			system("cls");
			this->welcomePage();
			this->showMenu();
		}break;
		case 0:
		{
			this->writeMenuToFile();
			return;
		}break;
		default:
		{
			return;
		}
		}
	}
}
#pragma endregion

#pragma region DRINK MANIPULATION

void Coffee_Shop::addDrink()
{
	int choice;
	
	cout << "Choose drink type: " << endl;
	cout << "1. Coffee" << endl;
	cout << "2. Tea" << endl;
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
			SetConsoleTextAttribute(hConsole, 14);
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
		this->addCoffee();
	}break;
	case 2:
	{
		this->addTea();
	}break;
	default:
	{

	}
	}
}

void Coffee_Shop::addCoffee()
{
	string n;
	float p;
	int h;
	cout << "Coffee name: ";
	cin >> n;
	cout << "Coffee price: ";
	try
	{
		cin >> p;
		while (cin.fail())
		{
			cin.clear();
			char c;
			while (cin.get(c) && c != '\n') {}
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 4);
			cerr << "Please enter a number" << endl;
			SetConsoleTextAttribute(hConsole, 14);
			cin >> p;
		}
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
	cout << "Coffee type (1-cold,2-hot): ";
	try
	{
		cin >> h;
		while (cin.fail() || h > 2)
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
			SetConsoleTextAttribute(hConsole, 14);
			cin >> h;
		}
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
	Coffee* coffee = new Coffee((coffeeType)(h-1), n, p);
	Beverage** tmp = this->menu;
	this->menuSize++;
	this->menu = new Beverage * [this->menuSize];
	for (int i = 0; i < menuSize - 1; i++)
	{
		this->menu[i] = new Coffee;
		this->menu[i] = tmp[i];
	}
	this->menu[this->menuSize - 1] = coffee;
	delete[] tmp;
}

void Coffee_Shop::addTea()
{
	string n;
	float p;
	int h;
	cout << "Tea name: ";
	cin >> n;
	cout << "Tea price: ";
	try
	{
		cin >> p;
		while (cin.fail())
		{
			cin.clear();
			char c;
			while (cin.get(c) && c != '\n') {}
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 4);
			cerr << "Please enter a number" << endl;
			SetConsoleTextAttribute(hConsole, 14);
			cin >> p;
		}
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
	cout << "Tea type (1-teabag,2-looseLeaf): ";
	try
	{
		cin >> h;
		while (cin.fail() || h > 2)
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
			SetConsoleTextAttribute(hConsole, 14);
			cin >> h;
		}
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
	Tea* tea = new Tea((teaType)(h-1), n, p);
	Beverage** tmp = this->menu;
	this->menuSize++;
	this->menu = new Beverage * [this->menuSize];
	for (int i = 0; i < menuSize - 1; i++)
	{
		this->menu[i] = new Tea;
		this->menu[i] = tmp[i];
	}
	this->menu[this->menuSize - 1] = tea;
	delete[] tmp;
}

void Coffee_Shop::editDrinkPrice()
{
	int drink;
	float price;
	cout << "Choose the drink which price you want to edit: ";
	try
	{
		cin >> drink;
		while (cin.fail() || drink > this->menuSize)
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
			SetConsoleTextAttribute(hConsole, 14);
			cin >> drink;
		}
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
	cout << "Enter the new price: ";
	try
	{
		cin >> price;
		while (cin.fail())
		{
			cin.clear();
			char c;
			while (cin.get(c) && c != '\n') {}
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 4);
			cerr << "Please enter a number" << endl;
			SetConsoleTextAttribute(hConsole, 14);
			cin >> price;
		}
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
	this->menu[drink - 1]->editPrice(price);
}

void Coffee_Shop::deleteDrink()
{
	int drink;
	cout << "Choose the drink you want to delete: ";
	try
	{
		cin >> drink;
		while (cin.fail() || drink > this->menuSize)
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
			SetConsoleTextAttribute(hConsole, 14);
			cin >> drink;
		}
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
	this->menuSize--;
	delete this->menu[drink - 1];
	this->menu[drink - 1] = this->menu[this->menuSize];
}
#pragma endregion

#pragma region FILE MANIPULATION
void Coffee_Shop::writeMenuToFile()
{
	this->menuFile.open(FILENAME, ios::out);
	this->menuFile << this->menuSize << endl;
	for (int i = 0; i < this->menuSize; i++)
	{
		if (typeid(*this->menu[i]) == typeid(Coffee))
		{
			this->menuFile << 0 << endl;
		}
		else
		{
			this->menuFile << 1 << endl;
		}
		this->menu[i]->writeToFile(&this->menuFile);
	}
	this->menuFile.close();
}

void Coffee_Shop::readMenuFromFile()
{
	int flg;
	this->menuFile.open(FILENAME, ios::in);
	this->menuFile >> this->menuSize;
	this->menu = new Beverage * [this->menuSize];
	for (int i = 0; i < this->menuSize; i++)
	{
		this->menuFile >> flg;
		if (flg == 0)
		{
			Coffee* c = new Coffee();
			this->menu[i] = c;
		}
		else
		{
			Tea* c = new Tea();
			this->menu[i] = c;
		}
		this->menu[i]->readFromFile(&this->menuFile);
	}
	this->menuFile.close();
}
#pragma endregion

#pragma region SOKCKET COMMUNICATION
void Coffee_Shop::configureServer()
{
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	int server = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	address.sin_port = htons(2000);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;

	int res = bind(server, (struct sockaddr*) & address, sizeof(address));

	if (res == 0)
	{
		res = listen(server, 10);

		if (res == 0)
		{
			struct sockaddr_in clientAddr;
			int clientAddrSize = sizeof(clientAddr);
			int client = accept(server,(struct sockaddr*) & clientAddr, &clientAddrSize);
			if (client >= 0)
			{
				char buffer[20];
				strcpy(buffer, this->name.c_str());
				send(client, buffer, sizeof(buffer),0);
			}
			else
			{
				cout << "Couldn't accept connection" << endl;
			}
		}
		else
		{
			cout << "Error in server listening" << endl;
		}
	}
	else
	{
		cout << "Error in server binding" << endl;
	}
	WSACleanup();
}
#pragma endregion