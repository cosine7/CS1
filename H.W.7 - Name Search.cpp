/*
Name: ChenXiao Liu
Honor Code: I have neither given nor received unauthorized aid in completing this work,
nor have I presented someone else's work as my own.


Name Search
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void readname(string[], int, ifstream&);
void check(string[], int, string);

int main()
{
	ifstream input;

	const int BOY = 1,
		  GIRL = 2,
		  QUIT = 3,
	          SIZE = 200;

	string choice,
	       name,
	       boy[SIZE],
	       girl[SIZE];

	int choice2;

	do
	{
		// Menu.
		cout << "What do you want to do?\n"
			<< " 1. See whether a boy's name is popular\n"
			<< " 2. See whether a girl's name is popular\n"
			<< " 3. Quit this program\n"
			<< "Please enter a number: ";
		getline(cin,choice);

		// Check if user entered correctly.
		while (choice != "1" && choice != "2" && choice != "3")
		{
			cout << "\nYou can only enter \"1\" \"2\" \"3\"."
				 << "\nPlease enter again: ";
			getline(cin, choice);
		}
		
		// Switching users' choice from string to integer.
		choice2 = stoi(choice);

		switch (choice2)
		{
		case BOY:
			input.open("C:/Users/BoyNames.txt");

			if (input.fail())
			{
				cout << "Input failed.\n";
				system("pause");
				exit(1);
			}

			readname(boy, SIZE, input);
			input.close();

			cout << "\nPlease enter a boy's name: ";
			getline(cin, name);

			check(boy, SIZE, name);

			break;
		case GIRL:
			input.open("C:/Users/GirlNames.txt");

			if (input.fail())
			{
				cout << "Input failed.\n";
				system("pause");
				exit(1);
			}

			readname(girl, SIZE, input);
			input.close();

			cout << "\nPlease enter a girl's name: ";
			getline(cin, name);

			check(girl, SIZE, name);

			break;
		}
	} while (choice != "3");

	system("pause");
	return 0;
}

// The "readname" function used for reading all names from a .txt file into a string array.
void readname(string name[], int size, ifstream& in)
{
	string data;

	for (int i = 0; i < size; i++)
	{
		in >> data;
		name[i] = data;
	}
}

// The "check" function used for checking the name that users entered.
void check(string names[], int sizes, string InName)
{
	int j;

	while (InName.length() < 2)
	{
		cout << "\nThis is not a name!"
			 << "\nPlease enter again: ";
		getline(cin, InName);
	}

	// Check each name stored in the string array.
	for (j = 0; j < sizes; j++)
	{
		if (names[j] == InName)
		{
			cout << "\n--------------------------------------\n"
				<< "This is one of the most popular names.\n"
				<< "--------------------------------------\n\n";
			j = -1;
			break;
		}
	}

	if (j != -1)
	{
		cout << "\n---------------------------\n"
			<< "This is not a popular name.\n"
			<< "---------------------------\n\n";
	}
}
