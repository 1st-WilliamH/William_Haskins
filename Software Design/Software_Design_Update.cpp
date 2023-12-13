// Software Design Update for CS 499, by William Haskins.
//
#include<iostream>
#include <fstream>
#include <string>

using namespace std;

string request;
string content;

//
//Encoder to secure external file information.
string Encoder(string decodedString)
{
	int encodingNumber = 5;
	string encodedString;

	for (int i = 0; i < decodedString.length(); i++)
	{
		int asciiValue = int(decodedString[i]);
		if (asciiValue == 32)
		{
			encodedString.push_back(char(asciiValue));
		}
		else
		{
			encodedString.push_back(char(asciiValue + encodingNumber));
		}
	}
	return encodedString;
}
//
//Decoder to retrieve data from external files.
string Decoder(string encodedString)
{
	int encodingNumber = 5;
	string decodedString;

	for (int i = 0; i < encodedString.length(); i++)
	{
		int asciiValue = int(encodedString[i]);
		if (asciiValue == 32)
		{
			decodedString.push_back(char(asciiValue));
		}
		else
		{
			decodedString.push_back(char(asciiValue - encodingNumber));
		}
	}
	return decodedString;
}
//
//Creates new client info.
int AddClient()
{
	string clientFirstName;
	string clientLastName;
	int newService;
	string theService;

	cout << "Enter the new client's first name\n";
	cin >> clientFirstName;
	cout << "Enter the new client's last name\n";
	cin >> clientLastName;
	cout << "And what type of service will this be? (1 = Brokerage, 2 = Retirement)\n";
	cin >> newService;

	if (newService == 1)
	{
		theService = Encoder("Brokerage");
	}
	else if (newService == 2)
	{
		theService = Encoder("Retirement");
	}
	else
	{
		cout << "\nThere was an error with the new client's details.\nReturning to main menu.\n";
		return 0;
	}

	ifstream streamFile("Account_Names.txt");
	ofstream writeFile("Account_Names_Temp.txt");
	if (!streamFile || !writeFile)
	{
		cerr << "Unable to open a file.\n";
		exit(1); //calls system to stop.
	}

	string content;

	int updateFlag = 1; //Checks for redacted indexes to fill.

	int accountIndex = 1;
	int i = 0;
	for (int i = 0; (streamFile >> content); i++)
	{
		if (content == Encoder("+--REDACTED--"))
		{
			writeFile << Encoder(to_string(accountIndex)) << Encoder(". ") << Encoder(clientFirstName) << " " << Encoder(clientLastName) << Encoder(" selected ") << theService << endl;
			updateFlag = 2;
		}
		else if (content == Encoder("--"))
		{
			writeFile << "";
		}
		else if (content == Encoder("----+"))
		{
			writeFile << "";
		}
		else if (((i + 1) % 5) == (0))
		{
			writeFile << content << endl;
			accountIndex++;
		}
		else
		{
			writeFile << content << " ";
		}
	}
	if (updateFlag == 1)
	{
		writeFile << Encoder(to_string(accountIndex)) << Encoder(". ") << Encoder(clientFirstName) << " " << Encoder(clientLastName) << Encoder(" selected ") << theService << endl;
	}

	writeFile.close();
	streamFile.close();
	remove("Account_Names.txt");
	rename("Account_Names_Temp.txt", "Account_Names.txt");
	return 0;
}
//
//Reads and translates account file.
int DisplayInfo()
{
	ifstream streamFile("Account_Names.txt");
	if (!streamFile)
	{
		cerr << "Unable to open a file.\n";
		exit(1); //calls system to stop.
	}
	while (getline(streamFile, content))
	{
		cout << Decoder(content) << "\n";
	}
	streamFile.close();
	return 0;
}
//
//Allows account updates.
int ChangeCustomerChoice()
{
	int changeChoice = 1;
	int newService;

	cout << "Enter the number of the client that you wish to change\n";
	cin >> changeChoice;
	cout << "Please enter the client's new service choice (1 = Brokerage, 2 = Retirement)\n";
	cin >> newService;

	ifstream streamFile("Account_Names.txt");
	ofstream writeFile("Account_Names_Temp.txt"); //Will be used to update the account file.
	if (!streamFile || !writeFile)
	{
		cerr << "Unable to open a file.\n";
		exit(1); //calls system to stop.
	}

	string content;
	int i = 0;
	for (int j = 0; (streamFile >> content); j++)
	{
		if (((j+1)%5) == (0)) //Account service choice is the 5th string in each line, which may need to be updated.
		{                     //"j + 1" will be prepared to read that next 5th string since the content reader is sitting on the 4th string here. 
			if (i == changeChoice - 1)
			{
				cout << "Updating account from " << Decoder(content) << " to ";
				if (newService == 1)
				{
					content = Encoder("Brokerage");
				}
				if (newService == 2)
				{
					content = Encoder("Retirement");
				}
				cout << Decoder(content) << endl;
			}
			writeFile << content << endl;
			i++;
		}
		else
		{
			writeFile << content << " ";
		}
	}
	writeFile.close();
	streamFile.close();
	remove("Account_Names.txt");
	rename("Account_Names_Temp.txt", "Account_Names.txt");
	return 0;
}
//
//Deletes client info.
int DeleteClient() {

	int accountChoice;

	cout << "Enter the number of the client that you wish to be deleted\n";
	cin >> accountChoice;

	ifstream streamFile("Account_Names.txt");
	ofstream writeFile("Account_Names_Temp.txt");

	string content;
	int i = 0;
	for (int j = 0; (streamFile >> content); j++)
	{
		if (i == (accountChoice - 1)) //Check for the indexed line that needs to be deleted.
		{
			if (((j + 5) % 5) == (0)) //Account index is the 1st string in each line.
			{                        
				writeFile << Encoder("+--REDACTED--") << " ";
			}
			else if (((j + 1) % 5) == (0))
			{                         
				writeFile << Encoder("----+") << endl;
				i++;
			}
			else
			{
				writeFile << Encoder("--") << " ";
			}
		}
		else
		{
			if (((j + 1) % 5) == (0)) 
			{                         
				writeFile << content << endl;
				i++;
			}
			else
			{
				writeFile << content << " ";
			}
		}
	}
	cout << "Account number " << accountChoice << " has been deleted.\n";

	writeFile.close();
	streamFile.close();
	remove("Account_Names.txt");
	rename("Account_Names_Temp.txt", "Account_Names.txt");
	return 0;
}
//
//Decodes administrative file and checks for correct username and password.
//Testing note: Username is "username" and Password is "password".
int CheckUserPermissionAccess()
{
	string username;
	string usernameCheck;
	string password;
	string passwordCheck;

	ifstream streamFile("Admin.txt");
	if (!streamFile)
	{
		cerr << "Unable to open a file.\n";
		exit(1); //calls system to stop.
	}
	getline(streamFile, content);
	usernameCheck = Decoder(content);
	getline(streamFile, content);
	passwordCheck = Decoder(content);
	streamFile.close();

	int buffer = 2;

	cout << "Enter your username: \n";
	cin >> username;
	if (username != usernameCheck)
	{
		cout << "No recognized username." << endl;
		return buffer;
	}

	cout << "Enter your password: \n";
	cin >> password;
	if (password == passwordCheck)
	{
		buffer = 1;
	}
	else
	{
		cout << "Wrong password." << endl;
		return buffer;
	}
	return buffer;
}
//
//Main
int main()
{
	int index = 0;
	int choice = 0;

	cout << "Hello! Welcome to our investment Company\n";
	while (index == 0)
	{
		//Lets the user log in or exit.
		cout << "Enter 1 to log in, or 2 to exit.\n";
		cin >> choice;
		if (choice == 1)
		{
			int passwordBuffer = CheckUserPermissionAccess();
			if (passwordBuffer == 1)
			{
				//Keeps user logged in until they exit the program.
				while (index == 0)
				{
					cout << "\nWhat would you like to do?\n"
						<< "CREATE new client account (enter 1)\n"
						<< "READ client accounts (enter 2)\n"
						<< "UPDATE client account (enter 3)\n"
						<< "DELETE a client (enter 4)\n"
						<< "Exit the program. . (enter 5)\n";

					cin >> choice;

					cout << "You chose " << choice << endl;

					if (choice == 1)
					{
						AddClient();
					}
					else if (choice == 2)
					{
						DisplayInfo();
					}
					else if (choice == 3)
					{
						ChangeCustomerChoice();
					}
					else if (choice == 4)
					{
						DeleteClient();
					}
					else if (choice == 5)
					{
						index = 1;
						break;
					}
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
		}
		else if (choice == 2)
		{
			index = 1;
		}
		//Clears the reader.
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

