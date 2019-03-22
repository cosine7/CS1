/*
Name: ChenXiao Liu
Honor Code: I have never given nor received unauthorized aid in completing this work,
nor have I presented someone else's work as my own.



Wi-Fi Diagnostic Tree
*/

#include<iostream>
#include<string>
using namespace std;

void mistyping(string&);

int main()
{
	string answer;

	cout << "Reboot the computer and try to connect.\n"
	    << "Did that fix the problem? ";
	cin >> answer;
	mistyping(answer);

	if (answer == "no")
	{
		cout << "Reboot the router and try to connect.\n"
		    << "Did that fix the problem? ";
		cin >> answer;
		mistyping(answer);
	}
	if (answer == "no")
	{
		cout << "Make sure the cables between the router and modem are plugged in firmly.\n"
		    << "Did that fix the problem? ";
		cin >> answer;
		mistyping(answer);
	}
	if (answer == "no")
	{
		cout << "Move the router to a new location.\n"
		    << "Did that fix the problem? ";
		cin >> answer;
		mistyping(answer);
	}
	if (answer == "no")
	{
		cout << "Get a new router.\n\n";
	}

	system("pause");
	return 0;
}

void mistyping(string &ans)
{
	while (ans != "yes" && ans != "no")
	{
		cout << "\nYou can only enter \"yes\" or \"no\".\n"
		    << "Please enter again: ";
		cin >> ans;
	}

	return;
}
