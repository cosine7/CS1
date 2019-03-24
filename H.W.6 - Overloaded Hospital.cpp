/*
Name: ChenXiao Liu
Honor Code: I have never given nor received unauthorized aid in completing this work,
nor have I presented someone else's work as my own.



Overloaded Hospital
*/    

#include <iostream>
#include <iomanip>
using namespace std;

// Practicing overload functions.
void mistyping(int&);
void mistyping(double&);
double charge(int, double, double, double);
double charge(double, double);
double charge(double, double, double, int, double, double, double);

int main()
{
	int choice,
	    days;

	double DailyRate,
	       medication,
	       service,
	       er,
	       er_medication,
	       er_service;

	const int IN = 1,
	 	  OUT = 2,
	          ER = 3;

	cout << "what kind of patient are you?\n"
	    << "1. Inpatient      2. Outpatient      3. Emergency room inpatient\n"
	    << "Please enter the number: ";
	cin >> choice;

	while ((choice < IN) || (choice > ER))
	{
		cout << "you can only enter \"1\" or \"2\" or \"3\".\n"
	            << "Please enter again: ";
		cin >> choice;
	}

	cout << setprecision(2) << fixed << showpoint;

	switch (choice)
	{
	case IN:
		cout << "\nPlease enter the number of days you spent in the hospital: ";
		cin >> days;
		mistyping(days);

		cout << "Please enter the daily rate: ";
		cin >> DailyRate;
		mistyping(DailyRate);

		cout << "Please enter the hospital medication charges: ";
		cin >> medication;
		mistyping(medication);

		cout << "Please enter charges for hospital services: ";
		cin >> service;
		mistyping(service);

		cout << "\nYour total charge is $" << charge(days, DailyRate, medication, service) << ".\n\n";
		break;
	case OUT:
		cout << "\nPlease enter the hospital medication charges: ";
		cin >> medication;
		mistyping(medication);

		cout << "Please enter charges for hospital services: ";
		cin >> service;
		mistyping(service);

		cout << "\nYour total charge is $" << charge(medication, service) << ".\n\n";
		break;
	case ER:
		cout << "\nPlease enter emergency room charges: ";
		cin >> er;
		mistyping(er);

		cout << "Please enter charges of medication supplied in emergency room: ";
		cin >> er_medication;
		mistyping(er_medication);

		cout << "Please enter charges for emergency room services: ";
		cin >> er_service;
		mistyping(er_service);

		cout << "Please enter the number of days you spent in the hospital: ";
		cin >> days;
		mistyping(days);

		cout << "Please enter the daily rate: ";
		cin >> DailyRate;
		mistyping(DailyRate);

		cout << "Please enter the hospital medication charges: ";
		cin >> medication;
		mistyping(medication);

		cout << "Please enter charges for hospital services: ";
		cin >> service;
		mistyping(service);

		cout << "\nYour total charge is $" << charge(er, er_medication, er_service, days, DailyRate, medication, service) << ".\n\n";
		break;
	}
		
	system("pause");
	return 0;
}

void mistyping(int& data)
{
	while (data < 1)
	{
		cout << "Do not accept a number less than 1!\n"
		    << "Please enter again: ";
		cin >> data;
	}

	return;
}

void mistyping(double& data)
{
	while (data < 0)
	{
		cout << "Do not accept negative numbers for any data!\n"
		    << "Please enter again: ";
		cin >> data;
	}

	return;
}

double charge(int day, double rate, double med, double ser)
{
	return (day * rate + med + ser);
}

double charge(double med, double ser)
{
	return (med + ser);
}

double charge(double emr, double emr_med, double emr_ser, int day, double rate, double med, double ser)
{
	return (emr + emr_med + emr_ser + day * rate + med + ser);
}
