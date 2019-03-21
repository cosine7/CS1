/*
Name: ChenXiao Liu
Honor Code: I have never given nor received unauthorized aid in completing this work,
nor have I presented someone else's work as my own.



Restaurant Bill
*/

#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	const double MEALCOST = 88.67,
		     TAX = 0.0675,
		     TIP = 0.2;

	double total_tax = 0,
	       total_tip = 0;

	total_tax = MEALCOST * TAX;
	total_tip = (total_tax + MEALCOST) * TIP;

	cout << setprecision(2) << fixed
		<< "Meal Cost:  $" << MEALCOST << endl
		<< "Tax Amount: $" << total_tax << endl
		<< "Tip Amount: $" << total_tip << endl
		<< "Total Bill: $" << MEALCOST + total_tax + total_tip << endl;

	system("pause");
	return 0;
}
