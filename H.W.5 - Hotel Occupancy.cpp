/*
Name: ChenXiao Liu
Honor Code: I have never given nor received unauthorized aid in completing this work,
nor have I presented someone else's work as my own.



Hotel Occupancy
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int floor,
	    i,
	    total_room,
	    occupied_room,
	    sum_total = 0,
	    sum_occupied = 0;

	cout << "How many floors the hotel has? ";
	cin >> floor;

	while (floor < 1)
	{
		cout << "\nInput Validation: Do not accept a value less than 1 for the number of floors."
		    << "\nPlease enter again! ";
		cin >> floor;
	}

	for (i = 1; i <= floor; i++)
	{
		// There are no floor 13 in any America hospitals.
		if (i <= 12)
		{
			cout << "\nHow many rooms are there in the floor " << i << " ? ";
		}
		else 
		{
			cout << "\nHow many rooms are there in the floor " << (i + 1) << " ? ";
		}

		cin >> total_room;

		while (total_room < 10)
		{
			cout << "Input validation: Do not accept a value less than 10 for the number of rooms on a floor."
			    << "\nPlease enter again! ";
			cin >> total_room;
		}

		cout << "How many of them are occupied? ";
		cin >> occupied_room;

		while ((occupied_room < 0) || (occupied_room > total_room))
		{
			cout << "Do not accept a value less than 0 and larger than total rooms.\n"
			    << "Plese enter again! ";
			cin >> occupied_room;
		}
		
		sum_total += total_room;
		sum_occupied += occupied_room;
	}

	cout << setprecision(2) << fixed << showpoint
	    << "\n----------------------------------------------"
	    << "\nThere are " << sum_total << " rooms in this hotal.\n"
	    << "There are " << sum_occupied << " occupied rooms.\n"
	    << "There are " << sum_total - sum_occupied << " unoccupied rooms.\n"
	    << "The occupancy rate for this hotel is "
	    << static_cast<double>(sum_occupied) / sum_total * 100
	    << "%.\n\n\n";


	system("pause");
	return 0;
}
