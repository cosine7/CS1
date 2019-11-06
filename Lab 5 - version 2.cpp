/*
Name: ChenXiao Liu
Honor Code: I have neitehr given nor received unauthorized aid in completing this work,
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
#include <string>
using namespace std;

struct Player
{
	int *card;
	int *suit;
};

void suffle_cards(int&, int&, int*);
void display_cards(int, int);
void red();
void black();
inline void gotoxy(int, int);
void SelectionSort(Player&);
bool flush(int*);
bool royalFlush(int*);
char straight(int*);
char four_of_a_kind(int*);
char fullHouse(int*);
char three_of_a_kind(int*);
char twoPair(int*);
char pair_(int*);
void calcScore(int*, int&);
int maxIndex(int*, int);

int main()
{
	system("color e0");
	srand((unsigned)time(0));
	char again;
	bool played_once = false;

	do
	{
		Player player[5];
		int duplication[52] = { 0 };

		for (int i = 0; i < 5; i++)
		{
			player[i].card = new int[7];
			player[i].suit = new int[7];
		}

		// Clean the screen if the player wants to play again.
		if (played_once)
			system("cls");
		else
			played_once = true;

		// Shuffle five cards for each player.
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				suffle_cards(player[i].card[j], player[i].suit[j], duplication);
			}
		}

		// Shuffle extra two cards to player 1.
		suffle_cards(player[0].card[5], player[0].suit[5], duplication);
		suffle_cards(player[0].card[6], player[0].suit[6], duplication);

		// Copy extra two cards from palyer 1 to each player.
		for (int i = 1; i < 5; i++)
		{
			player[i].card[5] = player[0].card[5];
			player[i].card[6] = player[0].card[6];
			player[i].suit[5] = player[0].suit[5];
			player[i].suit[6] = player[0].suit[6];
		}

		// Display cards.
		cout << "\tPL1\t\tPL2\t\tPL3\t\tPL4\t\tPL5\n\t===\t\t===\t\t===\t\t===\t\t===\n";
		for (int i = 0; i < 5; i++)
		{
			cout << '\t';
			for (int j = 0; j < 5; j++)
			{
				display_cards(player[j].card[i], player[j].suit[i]);
			}
			cout << '\n';
		}
		black();
		cout << "\t--------------------------------------------------------------------\n";

		// Display extra two cards.
		gotoxy(2, 85);
		cout << "Extra Cards";
		gotoxy(3, 88);
		display_cards(player[0].card[5], player[0].suit[5]);
		gotoxy(4, 88);
		display_cards(player[0].card[6], player[0].suit[6]);

		for (int i = 0; i < 5; i++)
			SelectionSort(player[i]);

		// Calculate scores of 21 situations and choose the best one to each player.
		// 从7张牌中随机抽取5张牌，且不在乎五张牌的顺序，那么根据公式（7C5）可以得出一共有21种情况。
		// 因为只有21种情况，所以是可以做到把它们全部罗列出来的。
		// 全部罗列出来，就可以在不改变判断卡组类型机制的条件下，轻而易举地计算分数了。
		// 这应该是最笨的一种方法。我认为修改判断卡组类型机制是比较困难的（判断5张牌是不是Flush是很简单的， 但是判断7张牌中里面有没有Flush是很繁琐的），大概是智商不够。
		string cases[21] = { "01234", "01235", "01236", "01245", "01246", "01256", "01345", "01346", "01356", "01456", "02345", "02346", "02356", "02456", "03456", "12345", "12346", "12356", "12456", "13456", "23456" };
		Player temp;
		string tempCase, maxCase[5];
		int score[5], case_score[21], index;

		temp.card = new int[5];
		temp.suit = new int[5];

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 21; j++)
			{
				for (int k = 0; k < 5; k++)
				{
					tempCase = cases[j][k];
					temp.card[k] = player[i].card[stoi(tempCase)];
					temp.suit[k] = player[i].suit[stoi(tempCase)];
				}

				char temp_type = straight(temp.card);

				if (flush(temp.suit))
				{					
					if (royalFlush(temp.card)) // Royal Flush
					{
						case_score[j] = 1900000;
					}
					else if (temp_type) // Straight Flush
					{
						if (temp_type == '1')
							case_score[j] = 1700002 + temp.card[0];
						else
							case_score[j] = 1700001;
					}
					else // Flush
					{
						case_score[j] = 1100000;
						calcScore(temp.card, case_score[j]);
					}
					continue;
				}

				if (temp_type) // Straight
				{
					if (temp_type == '1')
						case_score[j] = 900002 + temp.card[0];
					else
						case_score[j] = 900001;
					continue;
				}

				temp_type = four_of_a_kind(temp.card);

				if (temp_type) // Four of a kind
				{
					if (temp_type == '1')
						case_score[j] = 1500022 + temp.card[0] * 10 + temp.card[4];
					else
						case_score[j] = 1500022 + temp.card[4] * 10 + temp.card[0];
					continue;
				}

				temp_type = fullHouse(temp.card);

				if (temp_type) // Full House
				{
					if (temp_type == '1')
						case_score[j] = 1300022 + temp.card[0] * 10 + temp.card[4];
					else
						case_score[j] = 1300022 + temp.card[4] * 10 + temp.card[0];
					continue;
				}

				temp_type = three_of_a_kind(temp.card);

				if (temp_type) // Three of a kind 
				{
					if (temp_type == '1')
						case_score[j] = 700222 + temp.card[2] * 100 + temp.card[4] * 10 + temp.card[3];
					else if (temp_type == '2')
						case_score[j] = 700222 + temp.card[2] * 100 + temp.card[4] * 10 + temp.card[0];
					else
						case_score[j] = 700222 + temp.card[2] * 100 + temp.card[1] * 10 + temp.card[2];
					continue;
				}

				temp_type = twoPair(temp.card);

				if (temp_type) // Two pair
				{
					if (temp_type == '1')
						case_score[j] = 500222 + temp.card[3] * 100 + temp.card[1] * 10 + temp.card[4];
					else if (temp_type == '2')
						case_score[j] = 500222 + temp.card[3] * 100 + temp.card[1] * 10 + temp.card[0];
					else
						case_score[j] = 500222 + temp.card[3] * 100 + temp.card[1] * 10 + temp.card[2];
					continue;
				}

				temp_type = pair_(temp.card);

				if (temp_type) // Pair
				{
					if (temp_type == '1')
						case_score[j] = 302222 + temp.card[1] * 1000 + temp.card[4] * 100 + temp.card[3] * 10 + temp.card[2];
					else if (temp_type == '2')
						case_score[j] = 302222 + temp.card[1] * 1000 + temp.card[4] * 100 + temp.card[3] * 10 + temp.card[0];
					else if (temp_type == '3')
						case_score[j] = 302222 + temp.card[3] * 1000 + temp.card[4] * 100 + temp.card[1] * 10 + temp.card[0];
					else
						case_score[j] = 302222 + temp.card[3] * 1000 + temp.card[2] * 100 + temp.card[1] * 10 + temp.card[0];
					continue;
				}

				// High Card
				case_score[j] = 0;
				calcScore(temp.card, case_score[j]);
			}			
			index = maxIndex(case_score, 21);
			score[i] = case_score[index];
			maxCase[i] = cases[index];
		}
		delete [] temp.card;
		delete [] temp.suit;

		gotoxy(8, 0);
		for (int i = 0; i < 5; i++)
		{
			cout << '\t';
			for (int j = 0; j < 5; j++)
			{
				tempCase = maxCase[j][i];
				display_cards(player[j].card[stoi(tempCase)], player[j].suit[stoi(tempCase)]);
			}
			cout << '\n';
		}
		black();

		cout << "\n\t";
		for (int i = 0; i < 5; i++)
		{
			if (score[i] == 1900000)
				cout << "Royal Flush     ";
			else if (score[i] > 1700000)
				cout << "Straight Flush  ";
			else if (score[i] > 1500000)
				cout << "Four of A Kind  ";
			else if (score[i] > 1300000)
				cout << "Full House      ";
			else if (score[i] > 1100000)
				cout << "Flush           ";
			else if (score[i] > 900000)
				cout << "Straight        ";
			else if (score[i] > 700000)
				cout << "Three of A Kind ";
			else if (score[i] > 500000)
				cout << "Two Pair        ";
			else if (score[i] > 300000)
				cout << "Pair            ";
			else
				cout << "High Card       ";
		}

		// Display each player's score.
		cout << "\n\nScore:  ";
		for (auto val : score)
			cout << val << "\t\t";

		index = maxIndex(score, 5);

		// Show the winner.
		red();
		gotoxy(18, index * 16 + 8);
		cout << "Winner!";

		// Check if other players' scores are same with the winner's score.
		for (int i = 0; i <5; i++)
		{
			if ((score[i] == score[index]) && (index != i))
			{
				gotoxy(18, i * 16 + 8);
				cout << "Winner!";
			}
		}

		for (int i = 0; i < 5; i++)
		{
			delete[] player[i].card;
			delete[] player[i].suit;
		}

		black();
		cout << "\n\nDo you want to play again? (y/n) ";
		cin >> again;		

	} while (tolower(again) == 'y');
	
	system("pause");
	return 0;
}

void suffle_cards(int &card, int &suit, int *dup)
{
	int num;
	
	do
	{
		num = rand() % 52;
	} while (dup[num]);

	dup[num] = 1;
	card = num % 13;
	suit = num / 13 + 3;
}

void red()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_RED);
}

// The "black" function used to change the font color to black.
void black()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN);
}

void display_cards(int card, int suit)
{
	black();
	switch (card)
	{
	case 12:   // Ace
		cout << " A";
		break;
	case 11:   // King
		cout << " K";
		break;
	case 10:   // Queen
		cout << " Q";
		break;
	case 9:    // Jack
		cout << " J";
		break;
	default:
		cout << setw(2) << card + 2;
		break;
	}

	if (suit < 5)
		red();

	cout << char(suit) << "\t\t";
}

inline void gotoxy(int x, int y)
{
	//I changed the position of x and y, so that it becomes gotoxy(row, column).
	COORD pos = { y, x };
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, pos);
}

// The "SelectionSort" function used to sort cards of each player.
void SelectionSort(Player &player)
{
	int minIndex, minValue;

	for (int start = 0; start < 7; start++)
	{
		minIndex = start;
		minValue = player.card[start];
		for (int index = start + 1; index < 7; index++)
		{
			if (player.card[index] < minValue)
			{
				minValue = player.card[index];
				minIndex = index;
			}
		}
		swap(player.card[minIndex], player.card[start]);
		swap(player.suit[minIndex], player.suit[start]);
	}
}

bool flush(int *suit)
{
	if ((suit[0] == suit[1]) && (suit[1] == suit[2]) && (suit[2] == suit[3]) && (suit[3] == suit[4]))
	{
		return true;
	}
	return false;
}

bool royalFlush(int *card)
{
	if ((card[0] == 8) && (card[1] == 9) && (card[2] == 10) && (card[3] == 11) && (card[4] == 12))
	{
		return true;
	}
	return false;
}

char straight(int *card)
{
	if ((card[0] + 1 == card[1]) && (card[1] + 1 == card[2]) && (card[2] + 1 == card[3]) && (card[3] + 1 == card[4]))
	{
		return '1';
	}
	if ((card[0] == 0) && (card[1] == 1) && (card[2] == 2) && (card[3] == 3) && (card[4] == 12)) // Straight begin with A
	{
		return '2';
	}
	return false;
}

char four_of_a_kind(int *card)
{
	if ((card[0] == card[1]) && (card[1] == card[2]) && (card[2] == card[3]) && (card[3] != card[4]))
	{
		return '1';
	}
	if ((card[0] != card[1]) && (card[1] == card[2]) && (card[2] == card[3]) && (card[3] == card[4]))
	{
		return '2';
	}
	return false;
}

char fullHouse(int *card)
{
	if ((card[0] == card[1]) && (card[1] == card[2]) && (card[2] != card[3]) && (card[3] == card[4]))
	{
		return '1';
	}
	if ((card[0] == card[1]) && (card[1] != card[2]) && (card[2] == card[3]) && (card[3] == card[4]))
	{
		return '2';
	}
	return false;
}

char three_of_a_kind(int *card)
{
	if ((card[0] == card[1]) && (card[1] == card[2]) && (card[2] != card[3]) && (card[3] != card[4]))
	{
		return '1';
	}
	if ((card[0] != card[1]) && (card[1] == card[2]) && (card[2] == card[3]) && (card[3] != card[4]))
	{
		return '2';
	}
	if ((card[0] != card[1]) && (card[1] != card[2]) && (card[2] == card[3]) && (card[3] == card[4]))
	{
		return '3';
	}
	return false;
}

char twoPair(int *card)
{
	if ((card[0] == card[1]) && (card[1] != card[2]) && (card[2] == card[3]) && (card[3] != card[4]))
	{
		return '1';
	}
	if ((card[0] != card[1]) && (card[1] == card[2]) && (card[2] != card[3]) && (card[3] == card[4]))
	{
		return '2';
	}
	if ((card[0] == card[1]) && (card[1] != card[2]) && (card[2] != card[3]) && (card[3] == card[4]))
	{
		return '3';
	}
	return false;
}

char pair_(int *card)
{
	if ((card[0] == card[1]) && (card[1] != card[2]) && (card[2] != card[3]) && (card[3] != card[4]))
	{
		return '1';
	}
	if ((card[0] != card[1]) && (card[1] == card[2]) && (card[2] != card[3]) && (card[3] != card[4]))
	{
		return '2';
	}
	if ((card[0] != card[1]) && (card[1] != card[2]) && (card[2] == card[3]) && (card[3] != card[4]))
	{
		return '3';
	}
	if ((card[0] != card[1]) && (card[1] != card[2]) && (card[2] != card[3]) && (card[3] == card[4]))
	{
		return '4';
	}
	return false;
}

void calcScore(int* card, int &score)
{
	score = score + (card[0] + 2) + (card[1] + 2) * 10 + (card[2] + 2) * 100 + (card[3] + 2) * 1000 + (card[4] + 2) * 10000;
}

int maxIndex(int *score, int size)
{
	int max = 0;

	for (int i = 1; i < size; i++)
	{
		if (score[max] < score[i])
			max = i;
	}
	return max;
}