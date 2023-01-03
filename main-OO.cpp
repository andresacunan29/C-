#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

#include <mysql/jdbc.h> 

#include <conio.h>

#include <iomanip>
using namespace std;

using namespace std;

// reads in a password without echoing it to the screen
string myget_passwd()
{
	string passwd;
	char ch;
	for (;;)
	{
		ch = 0;
		while (ch == 0)   // Ugh. Microsoft not following standards on getch, so need to keep reading until a new char is typed. 
			ch = _getch();           // get char WITHIOUT echo! (should really be getch(), but MS is not following standrads again.)
		if (ch == 13 || ch == 10) // if done ...
			break;           //  stop reading chars!
		cout << '*';  // dump * to screen
		passwd += ch;   // addd char to password
	}
	cin.sync(); // flush anything else in the buffer (remaining newline)
	cout << endl;  // simulate the enter that the user pressed


	// read until end of line ... so future getlines work. 
	string dummy;
	getline(cin, dummy);

	return passwd;
}

int main()
{
	// Database connection credentials.
	std::string hostname;
	std::string port;
	std::string username;
	std::string password;
	std::string database_name;

	// Prompt user for database credentials.
	std::cout << "Hostname: ";
	std::getline(std::cin, hostname);
	std::cout << "Port Number:";
	std::getline(std::cin, port);
	std::cout << "Username: ";
	std::getline(std::cin, username);
	std::cout << "Password: ";
	std::getline(std::cin, password);
	std::cout << "Database Name: ";
	std::getline(std::cin, database_name);


	return 0;
}

