/*
Name: ChenXiao Liu
Honor Code: I have never given nor received unauthorized aid in completing this work,
nor have I presented someone else's work as my own.



Search Benchmarks    
*/

#include <iostream>

using namespace std;

int linear(int[], int, int);
int binary(int[], int, int);

int main()
{
	const int SIZE = 20;
	int x[SIZE] = { 101, 142, 147, 189, 199, 207, 222, 234, 289, 296, 310, 319, 388, 394, 417, 429, 447, 521, 536, 600 },
	    y = 521,
		result1,
		result2;

	result1 = linear(x, SIZE, y);
	result2 = binary(x, SIZE, y);

	if (result1 == -1)
	{
		cout << "Did not find the number " << y << "\n\n";
	}

	if (result2 == -1)
	{
		cout << "Did not find the number " << y << "\n\n";
	}

	system("pause");

	return 0;
}

int linear(int a[], int size, int b)
{
	int i = 0,
		position = -1;
	bool found = false;

	while (i < size && !found)
	{
		if (a[i] == b)
		{
			found = true;
			position = i;
		}
		i++;
	}

	cout << "Linear Search: " << i << " times.\n\n";

	return position;
}

int binary(int a[], int size, int b)
{
	int first = 0,
		last = size - 1,
		middle,
		position = -1,
		j = 0;
	bool found = false;

	while (!found && first <= last)
	{
		middle = (first + last) / 2;

		if (a[middle] == b)
		{
			found = true;
			position = j;
		}
		else if (a[middle] > b)
		{
			last = middle - 1;
		}
		else
		{
			first = middle + 1;
		}
		j++;
	}

	cout << "Binary Search: " << j << " times.\n\n";

	return position;
}