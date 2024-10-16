#include "Coffe Shop.h"
#include "Coffee.h"
#include "Tea.h"
#include <windows.h>
#include <iostream>
#include <typeinfo>
#include <sstream>


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
	shutdown(this->serverFD, SD_BOTH);
	WSACleanup();
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

void Coffee_Shop::showOrders()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	cout << "PENDING ORDERS: " << endl;
	cout << left << setw(8) << "Number: " << setw(20) << "Drink name: " << setw(12) <<  "Cup size: " << setw(50) << "Toppings: "  << setw(8) << "Price: "  << setw(10) << "Customer: " << endl;
	SetConsoleTextAttribute(hConsole, 14);
	for (int i = 0; i < this->orderNumber; i++)
	{
		cout <<left << setw(8) << (i+1);
		this->pendingOrders[i]->showOrder();
	}
}

void Coffee_Shop::showMenu()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	cout << "~~~~~~~~~~ MENU ~~~~~~~~~~" << endl;
	cout << left << setw(8) << "Number: " << setw(10) << "Beverage: " << setw(20) << "Name: " << setw(8) << "Price : " << setw(8) << "Type: " << endl;
	SetConsoleTextAttribute(hConsole, 14);
	for (int i = 0; i < this->menuSize; i++)
	{
		cout << left << setw(8) << (i + 1);
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
		cout << "5. Show pending orders" << endl;
		cout << "6. Complete an order" << endl;
		cout << "0. Exit" << endl;
		try
		{
			cin >> choice;
			while(cin.fail() || choice > 6)
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
		case 5:
		{
			system("cls");
			this->welcomePage();
			this->showOrders();
		}break;
		case 6:
		{
			system("cls");
			this->welcomePage();
			this->showOrders();
			this->completeOrder();
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

#pragma region ORDER MANIPULATION
void Coffee_Shop::addOrder(Order *o)
{
	Order** tmp = this->pendingOrders;
	this->orderNumber++;
	this->pendingOrders = new Order * [this->orderNumber];
	for (int i = 0; i < this->orderNumber - 1; i++)
	{
		this->pendingOrders[i] = new Order;
		this->pendingOrders[i] = tmp[i];
	}
	this->pendingOrders[this->orderNumber - 1] = o;
	delete[] tmp;
}

void Coffee_Shop::deleteOrder(int order)
{
	this->orderNumber--;
	delete this->pendingOrders[order];
	this->pendingOrders[order] = this->pendingOrders[this->orderNumber];
}

void Coffee_Shop::completeOrder()
{
	int order;
	cout << "Choose the order you want to complete: ";
	try
	{
		cin >> order;
		while (cin.fail() || order > this->orderNumber)
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
			cin >> order;
		}
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
	this->deleteOrder(order - 1);
}
#pragma endregion

#pragma region USER MANIPULATION
int Coffee_Shop::addNewUser(string name, int balance)
{
	int cardNumber;
	if (this->userNumber == 0)
	{
		cardNumber = 1000000000;
	}
	else
	{
		cardNumber = this->users[this->userNumber - 1] + 1;
	}
	srand(static_cast<unsigned int>(time(0)));
	int pin = rand() % 10000;
	this->userNumber++;
	this->users.push_back(cardNumber);
	this->writeUserToFile(cardNumber, pin, name, balance, 10);
	return pin;
}
#pragma endregion

#pragma region FILE MANIPULATION
void Coffee_Shop::writeMenuToFile()
{
	this->menuFile.open(FILE_MENU, ios::out);
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
	this->menuFile.open(FILE_MENU, ios::in);
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

void Coffee_Shop::writeUserToFile(int card, int pin, string name, int balance, int points)
{
	this->userFile.open(FILE_USERS, ios::out | ios::app);
	if (this->userNumber != 0)
	{
		this->userFile << endl;
	}
	this->userFile << card << " " << pin << " " << name << " " << balance << " " << points;

	this->userFile.close();
}

void Coffee_Shop::readCardsFromFile()
{
	int i = 0;
	this->userFile.open(FILE_USERS, ios::in);
	while(!this->userFile.eof())
	{
		this->users.push_back(0);
		this->userFile >> this->users[i];
		string data;
		getline(this->userFile, data);
		i++;
	}
	this->userNumber = i;
	this->userFile.close();
}

string Coffee_Shop::readUserFromFile(int card)
{
	string data;
	this->userFile.open(FILE_USERS, ios::in);
	for(int i = 0; i <= card; i++)
	{
		getline(this->userFile, data);
	}
	this->userFile.close();
	return data;
}
#pragma endregion

#pragma region SOKCKET COMMUNICATION
void Coffee_Shop::configureServer()
{
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	this->serverFD = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	address.sin_port = htons(2000);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;

	int res = bind(this->serverFD, (struct sockaddr*) & address, sizeof(address));

	if (res == 0)
	{
		res = listen(this->serverFD, 10);

		if (res == 0)
		{
			DWORD threadID;
			HANDLE thr = CreateThread(NULL, 0, acceptClients, this, 0, &threadID);

			
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

}

DWORD WINAPI Coffee_Shop::acceptClients(LPVOID p)
{
	Coffee_Shop* instance = static_cast<Coffee_Shop*>(p);
	struct sockaddr_in clientAddr;
	int clientAddrSize = sizeof(clientAddr);
	while (1)
	{
		int client = accept(instance->serverFD, (struct sockaddr*)&clientAddr, &clientAddrSize);
		if (client >= 0)
		{
			int user;
			char buffer[20];
			int recvSize = recv(client, buffer, 20, 0);
			if (strcmp(buffer, CODE_REGISTER) == 0)
			{
				user = instance->userRegister(client);
				instance->sendMenu(client);
				recvSize = recv(client, buffer, 20, 0);
				if (strcmp(buffer, CODE_ORDER) == 0)
				{
					instance->receiveOrder(client, user);
				}
			}
			else if (strcmp(buffer, CODE_LOGIN) == 0)
			{
				user = instance->userLogin(client);
				instance->sendMenu(client);
				recvSize = recv(client, buffer, 20, 0);
				if (strcmp(buffer, CODE_ORDER) == 0)
				{
					instance->receiveOrder(client, user);
				}
			}
			else
			{

			}
			closesocket(client);
		}
		else
		{
			cout << "Couldn't accept connection" << endl;
		}
	}
	return 0;
}

int Coffee_Shop::userRegister(int client)
{
	char buffer[20];
	int recvSize = recv(client, buffer, 20, 0);
	string name = buffer;
	recvSize = recv(client, buffer, 20, 0);
	int balance = atoi(buffer);
	balance = this->addNewUser(name, balance);

	strcpy(buffer, to_string(this->users[this->userNumber - 1]).c_str());
	send(client, buffer, 20, 0);
	strcpy(buffer, to_string(balance).c_str());
	send(client, buffer, 20, 0);
	strcpy(buffer, to_string(10).c_str());
	send(client, buffer, 20, 0);
	
	return this->users[this->userNumber - 1];
}

int Coffee_Shop::userLogin(int client)
{
	char buffer[20];
	int recvSize = recv(client, buffer, 20, 0);
	int  card = atoi(buffer);
	int index = distance(this->users.begin(), find(this->users.begin(), this->users.end(), card));
	recvSize = recv(client, buffer, 20, 0);
	string pin = buffer;
	string data = this->readUserFromFile(index);
	string PIN;
	istringstream ss(data);
	getline(ss, PIN, ' ');
	getline(ss, PIN, ' ');
	if (PIN == pin)
	{
		strcpy(buffer, CODE_SUCCESS);
	}
	else
	{
		strcpy(buffer, CODE_ERROR);
	}
	send(client, buffer, 20, 0);
	
	getline(ss, PIN, ' ');
	strcpy(buffer, PIN.c_str());
	send(client, buffer, 20, 0);
	getline(ss, PIN, ' ');
	strcpy(buffer, PIN.c_str());
	send(client, buffer, 20, 0);
	getline(ss, PIN, ' ');
	strcpy(buffer, PIN.c_str());
	send(client, buffer, 20, 0);

	return this->users[index];
}

void Coffee_Shop::sendMenu(int client)
{
	char buffer[20];
	string message;
	strcpy(buffer, this->name.c_str());
	send(client, buffer, 20, 0);
	message = to_string(this->menuSize);
	strcpy(buffer, message.c_str());
	send(client, buffer, 20, 0);
	for (int i = 0; i < this->menuSize; i++)
	{
		if (typeid(*this->menu[i]) == typeid(Coffee))
		{
			strcpy(buffer, "Coffee");
		}
		else
		{
			strcpy(buffer, "Tea");
		}
		send(client, buffer, 20, 0);
		strcpy(buffer, this->menu[i]->getName().c_str());
		send(client, buffer, 20, 0);
		message = to_string(this->menu[i]->getPrice());
		strcpy(buffer, message.c_str());
		send(client, buffer, 20, 0);
		strcpy(buffer, this->menu[i]->getTypeString().c_str());
		send(client, buffer, 20, 0);
	}
}

void Coffee_Shop::receiveOrder(int client, int card)
{
	char buffer[20];
	int recvSize = recv(client, buffer, 20, 0);
	int numb = atoi(buffer);
	Order* o = new Order(this->menu[numb], card);
	recvSize = recv(client, buffer, 20, 0);
	numb = atoi(buffer);
	o->addCupSize((cupSize)numb);
	recvSize = recv(client, buffer, 20, 0);
	numb = atoi(buffer);
	while (numb > 0)
	{
		o->addTopping((topping)(numb % 10));
		numb = numb / 10;
	}
	if (recvSize > 0)
	{
		this->addOrder(o);
		o->calculatePrice();
	}
}
#pragma endregion