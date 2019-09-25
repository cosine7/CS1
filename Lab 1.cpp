/*
Name: ChenXiao Liu
Honor Code: I have neither given nor received unauthorized aid in completing this work,
nor have I presented someone else's work as my own.



MCS1514 - Lab 1 - Spring 2019    

This program reads information of several employees from a .txt file,
then calculates their payrolls and print them both into a .txt file and on the screen.


*/

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int process_employee(ifstream& ,int&, double&, int&);
void process_payroll(ofstream&, double&, double&, double&, double&, double&);
void print_summary(ofstream&, double, double, double, double, double);

int main()
{
	
	ofstream output;  // Input files used in the function "process_payroll".

	double total_gross = 0,
		   total_net = 0,
		   total_fed = 0,
		   total_state = 0,
		   total_soc = 0;

	output.open("out.txt");

	if (output.fail())
	{
		cout << "output failed!\n";
		system("pause");
		exit(1);
	}

	cout << setprecision(2) << fixed << showpoint;
	output << setprecision(2) << fixed << showpoint;

	process_payroll(output, total_gross, total_net, total_fed, total_state, total_soc);
	print_summary(output, total_gross, total_net, total_fed, total_state, total_soc);

	output.close();

	system("pause");

	return 0;
}

// Function "process_employee" used for reading employee number, hourly wage, and hours worked from a .txt file.
int process_employee(ifstream& in, int& num, double& rat, int& hou)
{
	if (in >> num >> rat >> hou)
	{
		return 1;
	}
	
	return 0;
}

// Function "process_payroll" used for calculating employees' gross pay,net pay, fed tax, state tax, soc security tax and printing them.
void process_payroll(ofstream& out, double& t_gross, double& t_net, double& t_fed, double& t_state, double& t_soc)
{
	ifstream input;
	int number, hour;
	double rate;

	cout << "Employee Payroll\n\n"
		 << "Employee    Hours    Rate    Gross      Net     Fed    State    Soc Sec\n\n";
	out << "Employee Payroll\n\n"
		<< "Employee    Hours    Rate    Gross      Net     Fed    State    Soc Sec\n\n";

	input.open("C:/Users/a.txt");

	if (input.fail())
	{
		cout << "Input failed!\n";
		system("pause");
		exit(1);
	}

	while (process_employee(input, number, rate, hour))
	{
		double gross,
			   net,
			   fed,
			   state,
			   soc;

		const double FEDRAL_TAX = 0.16,
			         STATE_TAX = 0.0542,
			         SOCIAL_SECURITY_TAX = 0.07;

		if (hour <= 35)
		{
			gross = hour * (0.15 + rate);
			fed = gross * FEDRAL_TAX;
			state = gross * STATE_TAX;
			soc = gross * SOCIAL_SECURITY_TAX;
			net = gross - fed - state - soc;

			cout << setw(8) << number << setw(9) << hour << "*" << setw(7) << rate << setw(9) << gross << setw(9) << net << setw(8) << fed << setw(9) << state << setw(11) << soc << "\n\n";
			out << setw(8) << number << setw(9) << hour << "*" << setw(7) << rate << setw(9) << gross << setw(9) << net << setw(8) << fed << setw(9) << state << setw(11) << soc << "\n\n";
		}
		else if (hour > 40)
		{
			gross = 40 * rate + ((static_cast<double>(hour) - 40)) * 1.5 * rate;
			fed = gross * FEDRAL_TAX;
			state = gross * STATE_TAX;
			soc = gross * SOCIAL_SECURITY_TAX;
			net = gross - fed - state - soc;

			cout << setw(8) << number << setw(9) << hour << "$" << setw(7) << rate << setw(9) << gross << setw(9) << net << setw(8) << fed << setw(9) << state << setw(11) << soc << "\n\n";
			out << setw(8) << number << setw(9) << hour << "$" << setw(7) << rate << setw(9) << gross << setw(9) << net << setw(8) << fed << setw(9) << state << setw(11) << soc << "\n\n";
		}
		else
		{
			gross = hour * rate;
			fed = gross * FEDRAL_TAX;
			state = gross * STATE_TAX;
			soc = gross * SOCIAL_SECURITY_TAX;
			net = gross - fed - state - soc;

			cout << setw(8) << number << setw(9) << hour << setw(8) << rate << setw(9) << gross << setw(9) << net << setw(8) << fed << setw(9) << state << setw(11) << soc << "\n\n";
			out << setw(8) << number << setw(9) << hour << setw(8) << rate << setw(9) << gross << setw(9) << net << setw(8) << fed << setw(9) << state << setw(11) << soc << "\n\n";
		}

		t_gross += gross;
		t_net += net;
		t_fed += fed;
		t_state += state;
		t_soc += soc;
	}

	input.close();
}

// Function "print_summary" used for printing total gross pay, total net pay, total federal tax, total state tax and total social security tax.
void print_summary(ofstream& of, double gross_pay, double net_pay, double federal_tax, double state_tax, double soc_security)
{
	cout << "SUMMARY - Totals for All Employees\n"
		 << "------------------------------------\n\n"
		 << "       Gross Pay    Net Pay    Federal Tax    State Tax    Soc Security\n\n"
		 << setw(16) << gross_pay << setw(11) << net_pay << setw(15) << federal_tax << setw(13) << state_tax << setw(16) << soc_security <<"\n\n";
	of << "SUMMARY - Totals for All Employees\n"
	   << "------------------------------------\n\n"
	   << "       Gross Pay    Net Pay    Federal Tax    State Tax    Soc Security\n\n"
	   << setw(16) << gross_pay << setw(11) << net_pay << setw(15) << federal_tax << setw(13) << state_tax << setw(16) << soc_security << "\n\n";
}
