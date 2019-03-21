/*
Name: ChenXiao Liu
Honor Code: I have never given nor received unauthorized aid in completing this work,
nor have I presented someone else's work as my own.



Word Game
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
	string name, city, college, profession, animal, petname;
	int age;

	cout << "Please enter your name:                        ";
	getline(cin, name);

	cout << "Please enter your age:                         ";
	cin >> age;
	cin.ignore();

	cout << "Please enter the name of the city you live in: ";
	getline(cin, city);

	cout << "Please enter the name of your college:         ";
	getline(cin, college);

	cout << "Please enter your profession:                  ";
	getline(cin, profession);

	cout << "Please enter the species of your pet:          ";
	getline(cin, animal);

	cout << "Please enter the name of your pet:             ";
	getline(cin, petname);

	cout << "\n\n\nThere once was a person named " << name
	    << " who lived in " << city
	    << ". At the age of " << age
	    << ", " << name
	    << " went to college at " << college
	    << ". " << name
	    << " graduated and went to work as a " << profession
	    << ". Then, " << name
	    << " adopted a(n) " << animal
	    << " named " << petname
	    << ". They both lived happily ever after!\n";

	system("pause");
	return 0;
}
