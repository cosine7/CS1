/*
Name: ChenXiao Liu
Honor Code: I have never given nor received unauthorized aid in completing this work,
nor have I presented someone else's work as my own.


Lab 5 - Poker Hands
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <iomanip>
#include <windows.h>
#include <cstdio>
using namespace std;

void display_cards(int[][7], int[][7]);
void display_cards(int[][5], int[][5]);
void SelectionSort(int[][5], int[][5]);
void SelectionSort(int[][5], int[][5], int);
inline void swap(int&, int&);
inline void gotoxy(int, int);
bool flush(int[][5], int);
bool royalFlush(int[][5], int);
bool straight(int[][5], int);
bool straight_begin_with_A(int[][5], int);
int four_of_a_kind(int[][5], int);
int fullHouse(int[][5], int);
int three_of_a_kind(int[][5], int);
int twoPair(int[][5], int);
int pair_(int[][5], int);
void calcScore(int[][5], long long[], int, int);
void bubbleSort(long long[], int[], int);
void red();
void black();

int main()
{
	system("color e0");
	srand((unsigned)time(0)); 
	char again;
	bool play_time = false;

	do
	{
		int card[5][7] = { 0 },
			suit[5][7] = { 0 },
			duplication[52] = { 0 },
			extraCard[2] = { 0 },
			extraSuit[2] = { 0 },
			player[5] = { 0,1,2,3,4 },
			tempCard[5][5],
			tempSuit[5][5];
		long long score[5] = { 0 };

		// Clean the screen if the player wants to play more than one time.
		if (play_time)
		{
			system("cls");
		}
		else
		{
			play_time = true;
		}

		// Shuffle five cards of each player.
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				int num = rand() % 52;
				card[i][j] = num % 13;

				while (duplication[num])
				{
					num = rand() % 52;
					card[i][j] = num % 13;
				}
				duplication[num] = 1;
				suit[i][j] = num / 13 + 3;
			}
		}

		// Shuffle extra two cards.
		for (int i = 0; i < 2; i++)
		{
			int num = rand() % 52;
			extraCard[i] = num % 13;

			while (duplication[num])
			{
				num = rand() % 52;
				extraCard[i] = num % 13;
			}
			duplication[num] = 1;
			extraSuit[i] = num / 13 + 3;
		}

		// Display cards.
		cout << "\tPL1\t\tPL2\t\tPL3\t\tPL4\t\tPL5\n\t===\t\t===\t\t===\t\t===\t\t===\n";
		display_cards(card, suit);
		black();
		cout << "\t--------------------------------------------------------------------\n";

		// Display extra two cards.
		gotoxy(2, 85);
		cout << "Extra Cards";
		for (int i = 0; i < 2; i++)
		{
			cout << setw(2);
			gotoxy(3 + i, 88);
			black();
			switch (extraCard[i])
			{
			case 12:   // Ace
				cout << " A";
				if (extraSuit[i] < 5)
				{
					red();
				}
				cout << char(extraSuit[i]) << "\t\t";
				break;
			case 11:   // King
				cout << " K";
				if (extraSuit[i] < 5)
				{
					red();
				}
				cout << char(extraSuit[i]) << "\t\t";
				break;
			case 10:   // Queen
				cout << " Q";
				if (extraSuit[i] < 5)
				{
					red();
				}
				cout << char(extraSuit[i]) << "\t\t";
				break;
			case 9:    // Jack
				cout << " J";
				if (extraSuit[i] < 5)
				{
					red();
				}
				cout << char(extraSuit[i]) << "\t\t";
				break;
			default:
				cout << setw(2) << extraCard[i] + 2;
				if (extraSuit[i] < 5)
				{
					red();
				}
				cout << char(extraSuit[i]) << "\t\t";
				break;
			}
		}

		// Add extra two cards to each player.
		for (int i = 0; i < 5; i++)
		{
			card[i][5] = extraCard[0];
			card[i][6] = extraCard[1];
			suit[i][5] = extraSuit[0];
			suit[i][6] = extraSuit[1];
		}

		// Calculate scores of 21 situations and choose the best one to each player.
		for (int i = 0; i < 5; i++)
		{
			long long tempScore[21] = { 0 };
			int cases[21] = { 12345,12346,12347,12356,12357,12367,12456,12457,12467,12567,13456,13457,13467,13567,14567,23456,23457,23467,23567,24567,34567 };
			for (int j = 0; j < 21; j++)
			{
				tempCard[i][0] = card[i][cases[j] % 10 - 1];
				tempCard[i][1] = card[i][cases[j] % 100 / 10 - 1];
				tempCard[i][2] = card[i][cases[j] % 1000 / 100 - 1];
				tempCard[i][3] = card[i][cases[j] % 10000 / 1000 - 1];
				tempCard[i][4] = card[i][cases[j] % 100000 / 10000 - 1];

				tempSuit[i][0] = suit[i][cases[j] % 10 - 1];
				tempSuit[i][1] = suit[i][cases[j] % 100 / 10 - 1];
				tempSuit[i][2] = suit[i][cases[j] % 1000 / 100 - 1];
				tempSuit[i][3] = suit[i][cases[j] % 10000 / 1000 - 1];
				tempSuit[i][4] = suit[i][cases[j] % 100000 / 10000 - 1];

				SelectionSort(tempCard, tempSuit, i);

				if (flush(tempSuit, i))
				{
					if (royalFlush(tempCard, i))
					{
						tempScore[j] = 100000000000;
					}
					else if (straight(tempCard, i))
					{
						tempScore[j] = 90000000000;
						calcScore(tempCard, tempScore, i, j);
					}
					else if (straight_begin_with_A(tempCard, i))
					{
						tempScore[j] = 90504030201;
					}
					else
					{
						tempScore[j] = 60000000000;
						calcScore(tempCard, tempScore, i, j);
					}
				}
				else if (straight(tempCard, i))
				{
					tempScore[j] = 50000000000;
					calcScore(tempCard, tempScore, i, j);
				}
				else if (straight_begin_with_A(tempCard, i))
				{
					tempScore[j] = 50504030201;
				}
				else if (four_of_a_kind(tempCard, i))
				{
					switch (four_of_a_kind(tempCard, i))
					{
					case 1:
						tempScore[j] = 80000000000 + (static_cast<long long>(tempCard[i][0]) + 2) * 100000000 + tempCard[i][4] + 2;
						break;
					case 2:
						tempScore[j] = 80000000000 + (static_cast<long long>(tempCard[i][4]) + 2) * 100000000 + tempCard[i][0] + 2;
						break;
					}
				}
				else if (fullHouse(tempCard, i))
				{
					switch (fullHouse(tempCard, i))
					{
					case 1:
						tempScore[j] = 70000000000 + (static_cast<long long>(tempCard[i][0]) + 2) * 100000000 + (static_cast<long long>(tempCard[i][4]) + 2) * 1000000;
						break;
					case 2:
						tempScore[j] = 70000000000 + (static_cast<long long>(tempCard[i][4]) + 2) * 100000000 + (static_cast<long long>(tempCard[i][0]) + 2) * 1000000;
						break;
					}
				}
				else if (three_of_a_kind(tempCard, i))
				{
					switch (three_of_a_kind(tempCard, i))
					{
					case 1:
						tempScore[j] = 40000000000 + (static_cast<long long>(tempCard[i][0]) + 2) * 100000000 + (static_cast<long long>(tempCard[i][4]) + 2) * 1000000 + (static_cast<long long>(tempCard[i][3]) + 2) * 10000;
						break;
					case 2:
						tempScore[j] = 40000000000 + (static_cast<long long>(tempCard[i][1]) + 2) * 100000000 + (static_cast<long long>(tempCard[i][4]) + 2) * 1000000 + (static_cast<long long>(tempCard[i][0]) + 2) * 10000;
						break;
					case 3:
						tempScore[j] = 40000000000 + (static_cast<long long>(tempCard[i][2]) + 2) * 100000000 + (static_cast<long long>(tempCard[i][1]) + 2) * 1000000 + (static_cast<long long>(tempCard[i][0]) + 2) * 10000;
						break;
					}
				}
				else if (twoPair(tempCard, i))
				{
					switch (twoPair(tempCard, i))
					{
					case 1:
						tempScore[j] = 30000000000 + (static_cast<long long>(tempCard[i][3]) + 2) * 100000000 + (static_cast<long long>(tempCard[i][0]) + 2) * 1000000 + (static_cast<long long>(tempCard[i][4]) + 2);
						break;
					case 2:
						tempScore[j] = 30000000000 + (static_cast<long long>(tempCard[i][4]) + 2) * 100000000 + (static_cast<long long>(tempCard[i][1]) + 2) * 1000000 + (static_cast<long long>(tempCard[i][0]) + 2);
						break;
					case 3:
						tempScore[j] = 30000000000 + (static_cast<long long>(tempCard[i][4]) + 2) * 100000000 + (static_cast<long long>(tempCard[i][0]) + 2) * 1000000 + (static_cast<long long>(tempCard[i][2]) + 2);
						break;
					}
				}
				else if (pair_(tempCard, i))
				{
					switch (pair_(tempCard, i))
					{
					case 1:
						tempScore[j] = 20000000000 + (static_cast<long long>(tempCard[i][0]) + 2) * 100000000 + (static_cast<long long>(tempCard[i][4]) + 2) * 1000000 + (static_cast<long long>(tempCard[i][3]) + 2) * 10000 + (static_cast<long long>(tempCard[i][2]) + 2) * 100;
						break;
					case 2:
						tempScore[j] = 20000000000 + (static_cast<long long>(tempCard[i][1]) + 2) * 100000000 + (static_cast<long long>(tempCard[i][4]) + 2) * 1000000 + (static_cast<long long>(tempCard[i][3]) + 2) * 10000 + (static_cast<long long>(tempCard[i][0]) + 2) * 100;
						break;
					case 3:
						tempScore[j] = 20000000000 + (static_cast<long long>(tempCard[i][2]) + 2) * 100000000 + (static_cast<long long>(tempCard[i][4]) + 2) * 1000000 + (static_cast<long long>(tempCard[i][1]) + 2) * 10000 + (static_cast<long long>(tempCard[i][0]) + 2) * 100;
						break;
					case 4:
						tempScore[j] = 20000000000 + (static_cast<long long>(tempCard[i][3]) + 2) * 100000000 + (static_cast<long long>(tempCard[i][2]) + 2) * 1000000 + (static_cast<long long>(tempCard[i][1]) + 2) * 10000 + (static_cast<long long>(tempCard[i][0]) + 2) * 100;
						break;
					}
				}
				else
				{
					tempScore[j] = 10000000000;
					calcScore(tempCard, tempScore, i, j);
				}
			}
			bubbleSort(tempScore, cases, 21);
			score[i] = tempScore[20];

			tempCard[i][0] = card[i][cases[20] % 10 - 1];
			tempCard[i][1] = card[i][cases[20] % 100 / 10 - 1];
			tempCard[i][2] = card[i][cases[20] % 1000 / 100 - 1];
			tempCard[i][3] = card[i][cases[20] % 10000 / 1000 - 1];
			tempCard[i][4] = card[i][cases[20] % 100000 / 10000 - 1];

			tempSuit[i][0] = suit[i][cases[20] % 10 - 1];
			tempSuit[i][1] = suit[i][cases[20] % 100 / 10 - 1];
			tempSuit[i][2] = suit[i][cases[20] % 1000 / 100 - 1];
			tempSuit[i][3] = suit[i][cases[20] % 10000 / 1000 - 1];
			tempSuit[i][4] = suit[i][cases[20] % 100000 / 10000 - 1];
		}

		// Display best cards after sort.
		gotoxy(8, 0);
		SelectionSort(tempCard, tempSuit);
		display_cards(tempCard, tempSuit);

		// Display cards type of each player.
		black();
		cout << "\n\t";
		for (int i = 0; i < 5; i++)
		{
			if (score[i] == 100000000000)
				cout << "Royal Flush     ";
			else if (score[i] > 90000000000)
				cout << "Straight Flush  ";
			else if (score[i] > 80000000000)
				cout << "Four of A Kind  ";
			else if (score[i] > 70000000000)
				cout << "Full House      ";
			else if (score[i] > 60000000000)
				cout << "Flush           ";
			else if (score[i] > 50000000000)
				cout << "Straight        ";
			else if (score[i] > 40000000000)
				cout << "Three of A Kind ";
			else if (score[i] > 30000000000)
				cout << "Two Pair        ";
			else if (score[i] > 20000000000)
				cout << "Pair            ";
			else
				cout << "High Card       ";
		}

		// Display each player's score.
		cout << "\n\nScore:  ";

		for (auto val : score)
		{
			cout << val << "\t";
		}
		bubbleSort(score, player, 5);

		// Show the winner.
		red();
		gotoxy(18, player[4] * 16 + 8);
		cout << "Winner!";

		// Check if other players' scores are same with the winner's score.
		for (int i = 3; i >= 0; i--)
		{
			if (score[i] == score[i + 1])
			{
				gotoxy(18, player[i] * 16 + 8);
				cout << "Winner!";
			}
		}

		black();
		cout << "\n\nDo you want to play again? (y/n) ";
		cin >> again;

	} while (tolower(again) == 'y');

	system("pause");
	return 0;
}

void display_cards(int cards[][7], int suits[][7])
{
	for (int i = 0; i < 5; i++)
	{
		cout << '\t';
		for (int j = 0; j < 5; j++)
		{
			black();
			switch (cards[j][i])
			{
			case 12:   // Ace
				cout << " A";
				if (suits[j][i] < 5)
				{
					red();
				}
				cout << char(suits[j][i]) << "\t\t";
				break;
			case 11:   // King
				cout << " K";
				if (suits[j][i] < 5)
				{
					red();
				}
				cout << char(suits[j][i]) << "\t\t";
				break;
			case 10:   // Queen
				cout << " Q";
				if (suits[j][i] < 5)
				{
					red();
				}
				cout << char(suits[j][i]) << "\t\t";
				break;
			case 9:    // Jack
				cout << " J";
				if (suits[j][i] < 5)
				{
					red();
				}
				cout << char(suits[j][i]) << "\t\t";
				break;
			default:
				cout << setw(2) << cards[j][i] + 2;
				if (suits[j][i] < 5)
				{
					red();
				}
				cout << char(suits[j][i]) << "\t\t";
				break;
			}
		}
		cout << '\n';
	}
}

void display_cards(int cards[][5], int suits[][5])
{
	for (int i = 0; i < 5; i++)
	{
		cout << '\t';
		for (int j = 0; j < 5; j++)
		{
			black();
			switch (cards[j][i])
			{
			case 12:   // Ace
				cout << " A";
				if (suits[j][i] < 5)
				{
					red();
				}
				cout << char(suits[j][i]) << "\t\t";
				break;
			case 11:   // King
				cout << " K";
				if (suits[j][i] < 5)
				{
					red();
				}
				cout << char(suits[j][i]) << "\t\t";
				break;
			case 10:   // Queen
				cout << " Q";
				if (suits[j][i] < 5)
				{
					red();
				}
				cout << char(suits[j][i]) << "\t\t";
				break;
			case 9:    // Jack
				cout << " J";
				if (suits[j][i] < 5)
				{
					red();
				}
				cout << char(suits[j][i]) << "\t\t";
				break;
			default:
				cout << setw(2) << cards[j][i] + 2;
				if (suits[j][i] < 5)
				{
					red();
				}
				cout << char(suits[j][i]) << "\t\t";
				break;
			}
		}
		cout << '\n';
	}
}

// The "SelectionSort" function used to sort cards of each player.
void SelectionSort(int cards[][5], int suits[][5], int x)
{
	int minIndex, minValue;

		for (int start = 0; start < 5; start++)
		{
			minIndex = start;
			minValue = cards[x][start];
			for (int index = start + 1; index < 5; index++)
			{
				if (cards[x][index] < minValue)
				{
					minValue = cards[x][index];
					minIndex = index;
				}
			}
			swap(cards[x][minIndex], cards[x][start]);
			swap(suits[x][minIndex], suits[x][start]);
		}
}

void SelectionSort(int cards[][5], int suits[][5])
{
	int minIndex, minValue;

	for (int i = 0; i < 5; i++)
	{
		for (int start = 0; start < 5; start++)
		{
			minIndex = start;
			minValue = cards[i][start];
			for (int index = start + 1; index < 5; index++)
			{
				if (cards[i][index] < minValue)
				{
					minValue = cards[i][index];
					minIndex = index;
				}
			}
			swap(cards[i][minIndex], cards[i][start]);
			swap(suits[i][minIndex], suits[i][start]);
		}
	}
}

// The "bubbleSort" function used to sort scores of each player.
void bubbleSort(long long total[], int ply[], int size)
{
	int maxElement, index;

	for (maxElement = size - 1; maxElement > 0; maxElement--)
	{
		for (index = 0; index < maxElement; index++)
		{
			if (total[index] > total[index + 1])
			{
				swap(total[index], total[index + 1]);
				swap(ply[index], ply[index + 1]);
			}
		}
	}
}

// The "swap" function used to swap elements of arrays during the sorting process.
inline void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

// The "gotoxy" function used to relocate the cursor.
inline void gotoxy(int x, int y)
{
	//I changed the position of x and y, so that it becomes gotoxy(row, column).
	COORD pos = { y, x };
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, pos);
}

// The "red" function used to change the font color to red.
// I learned it from https://blog.csdn.net/zz457887107/article/details/6612034
void red()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_RED);
}

// The "black" function used to change the font color to black.
void black()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN);
}

bool flush(int suits[][5], int x)
{
	if ((suits[x][0] == suits[x][1]) && (suits[x][1] == suits[x][2]) && (suits[x][2] == suits[x][3]) && (suits[x][3] == suits[x][4]))
	{
		return true;
	}
	return false;
}

bool royalFlush(int cards[][5], int x)
{
	if ((cards[x][0] == 8) && (cards[x][1] == 9) && (cards[x][2] == 10) && (cards[x][3] == 11) && (cards[x][4] == 12))
	{
		return true;
	}
	return false;
}
bool straight(int cards[][5], int x)
{
	if ((cards[x][0] + 1 == cards[x][1]) && (cards[x][1] + 1 == cards[x][2]) && (cards[x][2] + 1 == cards[x][3]) && (cards[x][3] + 1 == cards[x][4]))
	{
		return true;
	}
	return false;
}

bool straight_begin_with_A(int cards[][5], int x)
{
	if ((cards[x][0] == 0) && (cards[x][1] == 1) && (cards[x][2] == 2) && (cards[x][3] == 3) && (cards[x][4] == 12))
	{
		return true;
	}
	return false;
}

int four_of_a_kind(int cards[][5], int x)
{
	if (((cards[x][0] == cards[x][1]) && (cards[x][1] == cards[x][2]) && (cards[x][2] == cards[x][3]) && (cards[x][3] != cards[x][4])))
	{
		return 1;
	}
	if (((cards[x][0] != cards[x][1]) && (cards[x][1] == cards[x][2]) && (cards[x][2] == cards[x][3]) && (cards[x][3] == cards[x][4])))
	{
		return 2;
	}
	return 0;
}

int fullHouse(int cards[][5], int x)
{
	if (((cards[x][0] == cards[x][1]) && (cards[x][1] == cards[x][2]) && (cards[x][2] != cards[x][3]) && (cards[x][3] == cards[x][4])))
	{
		return 1;
	}
	if (((cards[x][0] == cards[x][1]) && (cards[x][1] != cards[x][2]) && (cards[x][2] == cards[x][3]) && (cards[x][3] == cards[x][4])))
	{
		return 2;
	}
	return 0;
}

int three_of_a_kind(int cards[][5], int x)
{
	if (((cards[x][0] == cards[x][1]) && (cards[x][1] == cards[x][2]) && (cards[x][2] != cards[x][3]) && (cards[x][3] != cards[x][4])))
	{
		return 1;
	}
	if (((cards[x][0] != cards[x][1]) && (cards[x][1] == cards[x][2]) && (cards[x][2] == cards[x][3]) && (cards[x][3] != cards[x][4])))
	{
		return 2;
	}
	if (((cards[x][0] != cards[x][1]) && (cards[x][1] != cards[x][2]) && (cards[x][2] == cards[x][3]) && (cards[x][3] == cards[x][4])))
	{
		return 3;
	}
	return 0;
}

int twoPair(int cards[][5], int x)
{
	if (((cards[x][0] == cards[x][1]) && (cards[x][1] != cards[x][2]) && (cards[x][2] == cards[x][3]) && (cards[x][3] != cards[x][4])))
	{
		return 1;
	}
	if (((cards[x][0] != cards[x][1]) && (cards[x][1] == cards[x][2]) && (cards[x][2] != cards[x][3]) && (cards[x][3] == cards[x][4])))
	{
		return 2;
	}
	if (((cards[x][0] == cards[x][1]) && (cards[x][1] != cards[x][2]) && (cards[x][2] != cards[x][3]) && (cards[x][3] == cards[x][4])))
	{
		return 3;
	}
	return 0;
}

int pair_(int cards[][5], int x)
{
	if (((cards[x][0] == cards[x][1]) && (cards[x][1] != cards[x][2]) && (cards[x][2] != cards[x][3]) && (cards[x][3] != cards[x][4])))
	{
		return 1;
	}
	if (((cards[x][0] != cards[x][1]) && (cards[x][1] == cards[x][2]) && (cards[x][2] != cards[x][3]) && (cards[x][3] != cards[x][4])))
	{
		return 2;
	}
	if (((cards[x][0] != cards[x][1]) && (cards[x][1] != cards[x][2]) && (cards[x][2] == cards[x][3]) && (cards[x][3] != cards[x][4])))
	{
		return 3;
	}
	if (((cards[x][0] != cards[x][1]) && (cards[x][1] != cards[x][2]) && (cards[x][2] != cards[x][3]) && (cards[x][3] == cards[x][4])))
	{
		return 4;
	}
	return 0;
}

void calcScore(int cards[][5], long long total[], int player, int x)
{
	total[x] = total[x] + (static_cast<long long>(cards[player][0]) + 2) + (static_cast<long long>(cards[player][1]) + 2) * 100 + (static_cast<long long>(cards[player][2]) + 2) * 10000 + (static_cast<long long>(cards[player][3]) + 2) * 1000000 + (static_cast<long long>(cards[player][4]) + 2) * 100000000;
}