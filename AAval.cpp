/*********************************************************
 *  Solution to CSC24400 Fall 2021 Project #1           *
 *    Author: A. Acuna                                  *
 *      Date: 09/2021                                    *
 *********************************************************/

#include<iostream>
#include<fstream>
#include<string>
using namespace std;
//function that reads file and store it in a 3D pointer
void fileread(char***& ptr, int& count, string filename)
{

	ifstream fin(filename); //to count number of games

	ifstream finn(filename);//to read data for every game
	if (fin.is_open())
	{
		char a;
		while (!fin.eof())
		{
			fin >> a;
			if (a == '?')
			{
				count++; //counting number of games
			}
		}
		ptr = new char** [count];
		for (int i = 0; i < count; i++)
		{
			ptr[i] = new char* [4];

			for (int j = 0; j < 4; j++)
			{
				ptr[i][j] = new char[4];
			}
		}
		char x = ' ';
		int c = -1;
		while (x != '!')
		{
			finn >> x;
			if (x == '?')
		
			{
				c++;
			}
			if (x == '!')
			{
				break;
			}
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					finn >> x;
					ptr[c][i][j] = x;
				}
			}
		}
	}
	
}
//func which is given a particular row number and column number, 
//and it check its respective row and coloum
bool checkCordinate(char** ptr, int x, int y, int& eliminateRow, int& eliminateCol)
{
	int RowCount = 0, colCount = 0;
	for (int i = 0; i < 4; i++)
	{
		//to avoid repetition 
		if (i == eliminateRow)
		{
			continue;
		}
		if (ptr[x][i] == 'x')
		{
			RowCount++;
		}
	}
	for (int j = 0; j < 4; j++)
	{
		if (j == eliminateCol)
		{
			continue;
		}
		if (ptr[j][y] == 'x')
		{
			colCount++;
		}

	}
	if (RowCount == 3)
	{
		eliminateRow = x;
		return true;
	}
	else if (colCount == 3)
	{
		eliminateCol = y;
		return true;
	}
	else
	{
		return false;
	}
}
//this func calls the checkWin function for every Cordinate
bool forcedWin(char** ptr, int& x, int& y)
{
	int victoryCount = 0; //as we have to count atleast 2 winning positions
	int eliminateRow = -1, eliminateCol = -1; //to avoid repetition
	int diagonalCount = 0; //check the matrix diagonally
	if (ptr[0][0] == 'x')
	{
		diagonalCount++;
	}
	if (ptr[1][1] == 'x')
	{
		//For the diagonal I tried to use the 
		//coordinates and manually to go up spot by spot. 
		diagonalCount++;
	}
	if (ptr[2][2] == 'x')
	{
		diagonalCount++;
	}
	if (ptr[3][3] == 'x')
	{
		diagonalCount++;
	}
	if (diagonalCount > 2)
	{
		victoryCount++;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			eliminateRow = -1, eliminateCol = -1;
			if (checkCordinate(ptr, i, j, eliminateRow, eliminateCol))
			{
				//storing the coordinates of a forced win
				x = i;
				y = j;
				victoryCount++;
			}

			if (victoryCount > 1)
			{
				return true;
			}
		}
	}
	return false;
}
// main function
int main(int argc, char* argv[])
{
	char*** ptr;
	int numOfGames = 0;
	int cordinateX = 0, cordinateY = 0;
	string name;
	cout << "Enter filename: "; cin >> name;
	// asking for the txt file 
	fileread(ptr, numOfGames, name);
	// for loop to check the conditions inside the number of games 
	for (int i = 0; i < numOfGames; i++)
	{
		cout << "Checking for game: " << i + 1 << endl;
		if (forcedWin(ptr[i], cordinateX, cordinateY))
	    
		{ 
			cout << "Forced Win for X" << endl;
			cout << "Cordinates: (" << cordinateX << "," << cordinateY << ")" << endl;
		}
		else
		{
			cout << "X does not have a forced win" << endl;
		}
		cout << endl;
	}
	return 0;
}