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
	cout << "Card number: " << this->membershipCard << endl;
	string zeroes;
	if (this->PIN < 1000)
	{
		zeroes = "0";
		if (this->PIN < 100)
		{
			zeroes = zeroes + "0";
			if (this->PIN < 10)
			{
				zeroes = zeroes + "0";
			}
		}
	}
	cout << "PIN: " << zeroes << this->PIN << endl;
	cout << "Name: " << this->name << endl;
	cout << "Balance: " << this->balance << endl;
	cout << "Membership points: " << this->membershipPoints << endl;
}

void User::eraseLines(int lines)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD pos = { static_cast<SHORT>(0), static_cast<SHORT>(0) };
	if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		pos = csbi.dwCursorPosition;
	}
	for (int i = 0; i < lines; i++)
	{
		pos.Y--;
		SetConsoleCursorPosition(hConsole, pos);
		cout << "                                                                             ";
	}
	pos.X = 0;
	SetConsoleCursorPosition(hConsole, pos);
}
#pragma endregion

#pragma region SOCKET MANIPULATION
void User::connectToCoffeeShop()
{
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		printf("WSAStartup failed: %d\n", result);
	}

	this->server = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	address.sin_port = htons(2000);
	address.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &address.sin_addr.s_addr);

	result = connect(this->server, (struct sockaddr*)&address, sizeof(address));

	if (result == 0)
	{
		account();
	}
	else
	{
		cout << "Coffee shop is currently closed" << endl;
	}
	closesocket(this->server);
	WSACleanup();
}

void User::account()
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
		signin();
	}break;
	case 2:
	{
		system("cls");
		login();
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

void User::signin()
{
	string name;
	cout << "Name: ";
	cin >> name;
	int balance;
	cout << "Balance: ";
	cin >> balance;
	this->changeName(name);
	this->addToBalance(balance);
	char buffer[20];
	strcpy(buffer, CODE_REGISTER);
	send(this->server, buffer, 20, 0);
	strcpy(buffer, name.c_str());
	send(this->server, buffer, 20, 0);
	string message;
	message = to_string(balance);
	strcpy(buffer, message.c_str());
	send(this->server, buffer, 20, 0);

	cout << "You have succesfully registered" << endl;
	int recvSize = recv(this->server, buffer, 20, 0);
	int card = atoi(buffer);
	this->membershipCard = card;
	cout << "Your card number is " << card << endl;
	recvSize = recv(this->server, buffer, 20, 0);
	card = atoi(buffer);
	this->PIN = card;
	string zeroes;
	if (card < 1000)
	{
		zeroes = "0";
		if (card < 100)
		{
			zeroes = zeroes + "0";
			if (card < 10)
			{
				zeroes = zeroes + "0";
			}
		}
	}
	cout << "Your PIN is " << zeroes << card << endl;
	recvSize = recv(this->server, buffer, 20, 0);
	card = atoi(buffer);
	this->membershipPoints = card;
	receiveMenu();
}

void User::login()
{
	int card;
	cout << "Card number: ";
	cin >> card;
	this->membershipCard = card;
	int pin;
	cout << "PIN: ";
	cin >> pin;
	this->PIN = pin;
	char buffer[20];
	strcpy(buffer, CODE_LOGIN);
	send(this->server, buffer, 20, 0);
	string message;
	message = to_string(card);
	strcpy(buffer, message.c_str());
	send(this->server, buffer, 20, 0);
	message = to_string(pin);
	strcpy(buffer, message.c_str());
	send(this->server, buffer, 20, 0);

	int recvSize = recv(this->server, buffer, 20, 0);
	if (strcmp(buffer, CODE_SUCCESS) == 0)
	{
		cout << "You have succesfully logged in" << endl;
		recvSize = recv(this->server, buffer, 20, 0);
		message = buffer;
		this->name = message;
		recvSize = recv(this->server, buffer, 20, 0);
		card = atoi(buffer);
		this->balance = card;
		recvSize = recv(this->server, buffer, 20, 0);
		card = atoi(buffer);
		this->membershipPoints = card;
		receiveMenu();
	}
	else
	{
		cout << "WRONG" << endl;
	}
}

void User::receiveMenu()
{
	char buffer[20];
	int recvSize = recv(this->server, buffer, 20, 0);
	cout << "***********************************************************************************************" << endl;
	cout << "                             Welcome to " << buffer << " coffee shop                       " << endl;
	cout << "***********************************************************************************************" << endl;
	cout << "~~~~~~~~~~ MENU ~~~~~~~~~~" << endl;
	cout << left << setw(8) << "Number: " << setw(10) << "Beverage: " << setw(20) << "Name: " << setw(8) << "Price : " << setw(8) << "Type: " << endl;
	int menuSize;
	recvSize = recv(this->server, buffer, 20, 0);
	menuSize = atoi(buffer);
	for (int i = 0; i < menuSize; i++)
	{
		cout << left << setw(8) << (i + 1);
		recvSize = recv(this->server, buffer, 20, 0);
		cout << left << setw(10) << buffer;
		recvSize = recv(this->server, buffer, 20, 0);
		cout << left << setw(20) << buffer;
		recvSize = recv(this->server, buffer, 20, 0);
		cout << left << setw(8) << buffer;
		recvSize = recv(this->server, buffer, 20, 0);
		cout << left << setw(5) << buffer << endl;
	}


	while (1)
	{
		int choice;
		cout << "Select an action: " << endl;
		cout << "1. Order" << endl;
		cout << "2. See your info" << endl;
		cout << "3. Logout" << endl;
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
			order(menuSize);
		}break;
		case 2:
		{
			this->showInfo();
		}break;
		case 3:
		{

		}break;
		case 0:
		{
			strcpy(buffer, CODE_EXIT);
			send(this->server, buffer, 20, 0);
			return;
		}break;
		default:
		{
			return;
		}
		}
	}
}

void User::order(int menuSize)
{
	char buffer[20];
	strcpy(buffer, CODE_ORDER);
	send(this->server, buffer, 20, 0);
	this->eraseLines(6);
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
	send(this->server, buffer, 20, 0);
	this->eraseLines(1);
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
	send(this->server, buffer, 20, 0);
	this->eraseLines(3);
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
		this->eraseLines(12);
	}
	message = to_string(toppings);
	strcpy(buffer, message.c_str());
	send(this->server, buffer, 20, 0);
}
#pragma endregion