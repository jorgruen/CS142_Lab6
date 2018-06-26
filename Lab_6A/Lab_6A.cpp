// Lab_6A.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <iomanip>
using namespace std;

void DisplayMenu()
{
	cout << "Menu: Please select one of the following options :" << endl;
	cout << "\t1 - Drop a single chip into one slot" << endl;
	cout << "\t2 - Drop multiple chips into one slot" << endl;
	cout << "\t3 - Show the options menu" << endl;
	cout << "\t4 - Quit the program" << endl;
	cout << endl;
}

int ComputeWinnings(int slotNumber)
{
	int slotValues [9] = { 100, 500, 1000, 0, 10000, 0, 1000, 500, 100 };
	return slotValues[slotNumber];
}

float CalculateAvgEarnings(float numChips, float totalEarnings)
{
	return totalEarnings / numChips;
}

void DisplayWinnings(int numChips, float winnings)
{
	cout << setprecision(2) << fixed;
	if (numChips == 1)
	{
		cout << "Winnings: $" << winnings << endl;
		cout << endl;
	}
	else if (numChips > 1)
	{
		cout << "Total winnings on " << numChips << " chips: $" << winnings << endl;
		float averageEarnings = CalculateAvgEarnings(numChips, winnings);
		cout << "Average winnings per chip: $" << averageEarnings << endl; //"setprecision(2) << fixed" is for rounding cents
		cout << endl;
	}
}

void DropChips(int numChips)
{
	int slotNumber;
	float winnings = 0;

	do {
		cout << "Which slot do you want to drop the chip in (0-8)? ";
		cin >> slotNumber;
		cout << endl;

		if (slotNumber < 0 || slotNumber > 8)
		{
			cout << "Invalid slot." << endl;
			cout << endl;
			return;
		}

	} while (slotNumber < 0 || slotNumber > 8);

	for (int i = 0; i < numChips; i++)
	{
		float chipLocation = slotNumber;

		if (numChips == 1)
		{
			cout << "*** Dropping chip into slot " << slotNumber << " ***" << endl;
		}

		//logic for when ball hits peg
		for (int j = 0; j < 12; j++)
		{
			if (chipLocation > 0 && chipLocation < 8)
			{
				int direction = rand() % 2;

				switch (direction)
				{
					case 0:
						chipLocation += 0.5;
						break;
					case 1:
						chipLocation -= 0.5;
				}
			}
			else if (chipLocation == 0)
			{
				chipLocation += 0.5;
			}
			else if (chipLocation == 8)
			{
				chipLocation -= 0.5;
			}

			//prints out path for single coin drop
			cout << setprecision(1) << fixed; //gives path output one decimal place
			if (numChips == 1)
			{
;				if (j == 0)
				{
					cout << "Path: [";
				}
				else if (j < 11)
				{
					cout << chipLocation << ", ";
				}
				else
				{
					cout << chipLocation << "]" << endl;
				}
			}
		}

		//accumulates winnings
		int slotEarnings = ComputeWinnings((int)chipLocation);
		winnings += slotEarnings;
	}

	DisplayWinnings(numChips, winnings);
}

enum InputType
{
	OptionNumber,
	NumberOfChips,
	SlotSelection
};

bool ValidateInput(int input, InputType type)
{
	switch (type)
	{
		case OptionNumber:
		{
			if (input < 1 || input > 4)
			{
				cout << "Invalid selection. Enter 3 to see options." << endl;
				cout << endl;
				return false;
			}
			else
				return true;
		}
		case NumberOfChips:
		{
			if (input <= 0)
			{
				cout << "Invalid number of chips." << endl;
				cout << endl;
				return false;
			}
			else
				return true;
		}
		case SlotSelection:
			if (input < 0 || input > 8)
			{
				cout << "Invalid slot." << endl;
				cout << endl;
				return false;
			}
			else
				return true;
		default:
			return false;
	}
}

int GetUserInput()
{
	int input;
	cin >> input;

	if (cin.fail()) //if input is not an int
	{
		cin.clear();
		cin.ignore(256, '\n');
		return -1; //returns -1 so ValidateInput will show error message
	}
	else
	{
		return input;
	}
}

int main()
{
	int seedVal = 42;
	srand(seedVal);
	
	cout << "Welcome to the Plinko simulator! Enter 3 to see options." << endl;
	cout << endl;

	bool isValid = false;
	bool isPlaying = true;

	do
	{
		int choice;

		//prompts until input is valid or after displaying options
		do {
			cout << "Enter your selection now : ";
			choice = GetUserInput();
			cout << endl;

			if (choice == 3)
			{
				DisplayMenu();
				choice = 0; //causes selection prompt to appear again
			}

			isValid = ValidateInput(choice, OptionNumber);

		} while (isValid == false);

		//action begins based on user selection
		switch (choice)
		{
		case 1:
			cout << "*** Drop a single chip ***" << endl;
			cout << endl;
			DropChips(1);
			break;
		case 2:
			cout << "*** Drop multiple chips ***";
			cout << endl;
			int numChips;
			cout << "How many chips do you want to drop (>0)? ";
			numChips = GetUserInput();

			if (ValidateInput(numChips, NumberOfChips) == false)
			{
				break;
			}

			DropChips(numChips);
			break;
		case 4:
			cout << "Goodbye!";
			isPlaying = false;
			return 0;
		}

	} while (isPlaying);

	return 0;
}