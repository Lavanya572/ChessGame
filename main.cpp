#include <SFML/Graphics.hpp>
#include <iostream>


#define LENGTH 8
#define PawnBLACK 1
#define PawnWHITE -1
#define RookBLACK 2
#define RookWHITE -2
#define KnightWHITE -3
#define KnightBLACK 3
#define BishopBLACK 4
#define BishopWHITE -4
#define QueenWHITE -5
#define QueenBLACK 5
#define KingBLACK 6
#define KingWHITE -6

using namespace sf;

struct position
{
	int x, y;
}oldPos, kingWhite, kingBlack, transformWhite , transformBlack;

int  size = 100, move = 0, x, y;
int board[8][8] =
{ 2, 3, 4, 5, 6, 4, 3, 2,
  1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
 -1,-1,-1,-1,-1,-1,-1,-1,
 -2,-3,-4,-5,-6,-4,-3,-2, };

int rookWRight = 0, rookWLeft = 0, kingWMove = 0;
int rookBRight = 0, rookBLeft = 0, kingBMove = 0;

int moving = 0; // 0 move white, 1 move black

int checkW = 0, checkB = 0;

int transformationW = 0, transformationB = 0;


int PawnW(int startx, int starty, int endx, int endy)
{
	if (oldPos.y == 6)
	{
		if ((endy == starty - 1 && endx == startx && board[starty - 1][startx] == 0) || (endy == starty - 2 && endx == startx && board[starty - 1][startx] == 0 && board[starty - 2][startx] == 0))
		{
			return 1;
		}
	}
	else if (endy == starty - 1 && endx == startx && board[starty - 1][startx] == 0)
	{
		return 1;
	}
	if (board[starty - 1][startx - 1] > 0)
	{
		if (endy == starty - 1 && endx == startx - 1)
		{
			return 1;
		}
	}
	if (board[starty - 1][startx + 1] > 0)
	{
		if (endy == starty - 1 && endx == startx + 1)
		{
			return 1;
		}
	}
	return 0;
}

int PawnB(int startx, int starty, int endx, int endy)
{
	if (oldPos.y == 1)
	{
		if ((endy == starty + 1 && endx == startx && board[starty + 1][startx] == 0) || (endy == starty + 2 && endx == startx && board[starty + 1][startx] == 0 && board[starty + 2][startx] == 0))
		{
			return 1;
		}
	}
	else if (endy == starty + 1 && endx == startx && board[starty + 1][startx] == 0)
	{
		return 1;
	}
	if (board[starty + 1][startx - 1] < 0)
	{
		if (endy == starty + 1 && endx == startx - 1)
		{
			return 1;
		}
	}
	if (board[starty + 1][startx + 1] < 0)
	{
		if (endy == starty + 1 && endx == startx + 1)
		{
			return 1;
		}
	}
	return 0;
}

int RookW(int startx, int starty, int endx, int endy)
{
	for (int i = startx - 1; i >= 0; i--) // spre stanga
	{
		if (board[starty][i] >= 0 && (endx == i && endy == starty))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty - 1; i >= 0; i--) // sus
	{
		if (board[i][startx] >= 0 && (endy == i && endx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	for (int i = startx + 1; i <= 7; i++) // spre dreapta
	{
		if (board[starty][i] >= 0 && (endy == starty && endx == i))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty + 1; i <= 7; i++) // jos
	{
		if (board[i][startx] >= 0 && (endy == i && endx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	return 0;
}

int RookB(int startx, int starty, int endx, int endy)
{
	for (int i = startx - 1; i >= 0; i--) // spre stanga
	{
		if (board[starty][i] <= 0 && (endx == i && endy == starty))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty - 1; i >= 0; i--) // sus
	{
		if (board[i][startx] <= 0 && (endy == i && endx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	for (int i = startx + 1; i <= 7; i++) // spre dreapta
	{
		if (board[starty][i] <= 0 && (endy == starty && endx == i))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty + 1; i <= 7; i++) // jos
	{
		if (board[i][startx] <= 0 && (endy == i && endx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	return 0;
}

int BishopW(int startx, int starty, int endx, int endy)
{
	int j = startx - 1;
	for (int i = starty - 1; i >= 0; i--) // spre stanga sus
	{
		if (board[i][j] >= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty - 1; i >= 0; i--) // spre dreapta sus
	{
		if (board[i][j] >= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = startx - 1;
	for (int i = starty + 1; i <= 7; i++) // spre stanga jos
	{
		if (board[i][j] >= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty + 1; i <= 7; i++)  // spre dreapta jos
	{
		if (board[i][j] >= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int BishopB(int startx, int starty, int endx, int endy)
{
	int j = startx - 1;
	for (int i = starty - 1; i >= 0; i--) // spre stanga sus
	{
		if (board[i][j] <= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty - 1; i >= 0; i--) // spre dreapta sus
	{
		if (board[i][j] <= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = startx - 1;
	for (int i = starty + 1; i <= 7; i++) // spre stanga jos
	{
		if (board[i][j] <= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty + 1; i <= 7; i++)  // spre dreapta jos
	{
		if (board[i][j] <= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int QueenW(int startx, int starty, int endx, int endy)
{
	for (int i = startx - 1; i >= 0; i--) // spre stanga
	{
		if (board[starty][i] >= 0 && (endx == i && endy == starty))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty - 1; i >= 0; i--) // sus
	{
		if (board[i][startx] >= 0 && (endy == i && endx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	for (int i = startx + 1; i <= 7; i++) // spre dreapta
	{
		if (board[starty][i] >= 0 && (endy == starty && endx == i))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty + 1; i <= 7; i++) // jos
	{
		if (board[i][startx] >= 0 && (endy == i && endx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	int j = startx - 1;
	for (int i = starty - 1; i >= 0; i--) // spre stanga sus
	{
		if (board[i][j] >= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty - 1; i >= 0; i--) // spre dreapta sus
	{
		if (board[i][j] >= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = startx - 1;
	for (int i = starty + 1; i <= 7; i++) // spre stanga jos
	{
		if (board[i][j] >= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty + 1; i <= 7; i++)  // spre dreapta jos
	{
		if (board[i][j] >= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int QueenB(int startx, int starty, int endx, int endy)
{
	for (int i = startx - 1; i >= 0; i--) // spre stanga
	{
		if (board[starty][i] <= 0 && (endx == i && endy == starty))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty - 1; i >= 0; i--) // sus
	{
		if (board[i][startx] <= 0 && (endy == i && endx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	for (int i = startx + 1; i <= 7; i++) // spre dreapta
	{
		if (board[starty][i] <= 0 && (endy == starty && endx == i))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty + 1; i <= 7; i++) // jos
	{
		if (board[i][startx] <= 0 && (endy == i && endx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	int j = startx - 1;
	for (int i = starty - 1; i >= 0; i--) // spre stanga sus
	{
		if (board[i][j] <= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty - 1; i >= 0; i--) // spre dreapta sus
	{
		if (board[i][j] <= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = startx - 1;
	for (int i = starty + 1; i <= 7; i++) // spre stanga jos
	{
		if (board[i][j] <= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty + 1; i <= 7; i++)  // spre dreapta jos
	{
		if (board[i][j] <= 0 && (endy == i && endx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int KnightW(int startx, int starty, int endx, int endy)
{
	if (starty - 2 >= 0 && startx - 1 >= 0 && endy == starty - 2 && endx == startx - 1 && board[endy][endx] >= 0)
	{
		return 1; // stanga sus
	}
	if (starty - 2 >= 0 && startx + 1 < LENGTH && endy == starty - 2 && endx == startx + 1 && board[endy][endx] >= 0)
	{
		return 1; // dreapta sus
	}
	if (starty - 1 >= 0 && startx + 2 < LENGTH && endy == starty - 1 && endx == startx + 2 && board[endy][endx] >= 0)
	{
		return 1; // dreapta 1
	}
	if (starty + 1 >= 0 && startx + 2 < LENGTH && endy == starty + 1 && endx == startx + 2 && board[endy][endx] >= 0)
	{
		return 1; // dreapta 2
	}
	if (starty + 2 < LENGTH && startx + 1 < LENGTH && endy == starty + 2 && endx == startx + 1 && board[endy][endx] >= 0)
	{
		return 1; // jos 1
	}
	if (starty + 2 < LENGTH && startx - 1 >= 0 && endy == starty + 2 && endx == startx - 1 && board[endy][endx] >= 0)
	{
		return 1; //jos 2
	}
	if (starty + 1 < LENGTH && startx - 2 >= 0 && endy == starty + 1 && endx == startx - 2 && board[endy][endx] >= 0)
	{
		return 1; // stanga 1
	}
	if (starty - 1 >= 0 && startx - 2 >= 0 && endy == starty - 1 && endx == startx - 2 && board[endy][endx] >= 0)
	{
		return 1;
	}
	return 0;
}

int KnightB(int startx, int starty, int endx, int endy)
{
	if (starty - 2 >= 0 && startx - 1 >= 0 && endy == starty - 2 && endx == startx - 1 && board[endy][endx] <= 0)
	{
		return 1; // stanga sus
	}
	if (starty - 2 >= 0 && startx + 1 < LENGTH && endy == starty - 2 && endx == startx + 1 && board[endy][endx] <= 0)
	{
		return 1; // dreapta sus
	}
	if (starty - 1 >= 0 && startx + 2 < LENGTH && endy == starty - 1 && endx == startx + 2 && board[endy][endx] <= 0)
	{
		return 1; // dreapta 1
	}
	if (starty + 1 >= 0 && startx + 2 < LENGTH && endy == starty + 1 && endx == startx + 2 && board[endy][endx] <= 0)
	{
		return 1; // dreapta 2
	}
	if (starty + 2 < LENGTH && startx + 1 < LENGTH && endy == starty + 2 && endx == startx + 1 && board[endy][endx] <= 0)
	{
		return 1; // jos 1
	}
	if (starty + 2 < LENGTH && startx - 1 >= 0 && endy == starty + 2 && endx == startx - 1 && board[endy][endx] <= 0)
	{
		return 1; //jos 2
	}
	if (starty + 1 < LENGTH && startx - 2 >= 0 && endy == starty + 1 && endx == startx - 2 && board[endy][endx] <= 0)
	{
		return 1; // stanga 1
	}
	if (starty - 1 >= 0 && startx - 2 >= 0 && endy == starty - 1 && endx == startx - 2 && board[endy][endx] <= 0)
	{
		return 1;
	}
	return 0;
}


int PawnWChess(int posx, int posy, int kingx, int kingy)
{
	//std::cout << "startx=" << posx << " starty=" << posy << " kingx=" << kingx << " kingy=" << kingy << "\n\n\n";
	if (board[posy - 1][posx - 1] >= 0)
	{
		if (posy - 1 == kingy && posx - 1 == kingx)
		{
			return 1;
		}
	}
	if (board[posy - 1][posx + 1] >= 0)
	{
		//std::cout << "da";
		if (posy - 1 == kingy && posx + 1 == kingx)
		{
			return 1;
		}
	}
	return 0;
}

int RookWChess(int startx, int starty, int kingx, int kingy)
{
	for (int i = startx - 1; i >= 0; i--) // spre stanga
	{
		if (board[starty][i] >= 0 && (kingx == i && kingy == starty))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty - 1; i >= 0; i--) // sus
	{
		if (board[i][startx] >= 0 && (kingy == i && kingx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	for (int i = startx + 1; i < LENGTH; i++) // spre dreapta
	{
		if (board[starty][i] >= 0 && (kingy == starty && kingx == i))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty + 1; i < LENGTH; i++) // jos
	{
		if (board[i][startx] >= 0 && (kingy == i && kingx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	return 0;
}

int BishopWChess(int startx, int starty, int kingx, int kingy)
{
	int j = startx - 1;
	for (int i = starty - 1; i >= 0; i--) // spre stanga sus
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty - 1; i >= 0; i--) // spre dreapta sus
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = startx - 1;
	for (int i = starty + 1; i <= 7; i++) // spre stanga jos
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty + 1; i <= 7; i++)  // spre dreapta jos
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int QueenWChess(int startx, int starty, int kingx, int kingy)
{
	for (int i = startx - 1; i >= 0; i--) // spre stanga
	{
		if (board[starty][i] >= 0 && (kingx == i && kingy == starty))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty - 1; i >= 0; i--) // sus
	{
		if (board[i][startx] >= 0 && (kingy == i && kingx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	for (int i = startx + 1; i < LENGTH; i++) // spre dreapta
	{
		if (board[starty][i] >= 0 && (kingy == starty && kingx == i))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty + 1; i < LENGTH; i++) // jos
	{
		if (board[i][startx] >= 0 && (kingy == i && kingx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	int j = startx - 1;
	for (int i = starty - 1; i >= 0; i--) // spre stanga sus
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty - 1; i >= 0; i--) // spre dreapta sus
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = startx - 1;
	for (int i = starty + 1; i <= 7; i++) // spre stanga jos
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty + 1; i < LENGTH; i++)  // spre dreapta jos
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int KnightWChess(int startx, int starty, int kingx, int kingy)
{
	if (starty - 2 >= 0 && startx - 1 >= 0 && kingy == starty - 2 && kingx == startx - 1 && board[kingy][kingx] >= 0)
	{
		return 1; // stanga sus
	}
	if (starty - 2 >= 0 && startx + 1 < LENGTH && kingy == starty - 2 && kingx == startx + 1 && board[kingy][kingx] >= 0)
	{
		return 1; // dreapta sus
	}
	if (starty - 1 >= 0 && startx + 2 < LENGTH && kingy == starty - 1 && kingx == startx + 2 && board[kingy][kingx] >= 0)
	{
		return 1; // dreapta 1
	}
	if (starty + 1 >= 0 && startx + 2 < LENGTH && kingy == starty + 1 && kingx == startx + 2 && board[kingy][kingx] >= 0)
	{
		return 1; // dreapta 2
	}
	if (starty + 2 < LENGTH && startx + 1 < LENGTH && kingy == starty + 2 && kingx == startx + 1 && board[kingy][kingx] >= 0)
	{
		return 1; // jos 1
	}
	if (starty + 2 < LENGTH && startx - 1 >= 0 && kingy == starty + 2 && kingx == startx - 1 && board[kingy][kingx] >= 0)
	{
		return 1; //jos 2
	}
	if (starty + 1 < LENGTH && startx - 2 >= 0 && kingy == starty + 1 && kingx == startx - 2 && board[kingy][kingx] >= 0)
	{
		return 1; // stanga 1
	}
	if (starty - 1 >= 0 && startx - 2 >= 0 && kingy == starty - 1 && kingx == startx - 2 && board[kingy][kingx] >= 0)
	{
		return 1;
	}
	return 0;
}

int KingWChess(int startx, int starty, int kingx, int kingy)
{
	if (startx - 1 >= 0 && starty - 1 >= 0 && kingy == starty - 1 && kingx == startx - 1 && board[kingy][kingx] <= 0)
	{
		return 1;
	}
	if (starty - 1 >= 0 && kingx == startx && kingy == starty - 1 && board[kingy][kingx] <= 0)
	{
		return 1;
	}
	if (starty - 1 >= 0 && startx + 1 < LENGTH && kingx == startx + 1 && kingy == starty - 1 && board[kingy][kingx] <= 0)
	{
		return 1;
	}
	if (startx + 1 < LENGTH && kingy == starty && kingx == startx + 1 && board[kingy][kingx] <= 0)
	{
		return 1;
	}
	if (startx + 1 < LENGTH && starty + 1 < LENGTH && kingy == starty + 1 && kingx == startx + 1 && board[kingy][kingx] <= 0)
	{
		return 1;
	}
	if (starty + 1 < LENGTH && kingy == starty + 1 && kingx == startx && board[kingy][kingx] <= 0)
	{
		return 1;
	}
	if (startx - 1 >= 0 && starty + 1 < LENGTH && kingx == startx - 1 && kingy == starty + 1 && board[kingy][kingx] <= 0)
	{
		return 1;
	}
	if (startx - 1 >= 0 && kingy == starty && kingx == startx - 1 && board[kingy][kingx] <= 0)
	{
		return 1;
	}
	return 0;
}


int PawnBChess(int startx, int starty, int kingx, int kingy)
{
	if (board[starty + 1][startx - 1] <= 0)
	{
		if (kingy == starty + 1 && kingx == startx - 1)
		{
			return 1;
		}
	}
	if (board[starty + 1][startx + 1] <= 0)
	{
		if (kingy == starty + 1 && kingx == startx + 1)
		{
			return 1;
		}
	}
	return 0;
}

int RookBChess(int startx, int starty, int kingx, int kingy)
{
	for (int i = startx - 1; i >= 0; i--) // spre stanga
	{
		if (board[starty][i] <= 0 && (kingx == i && kingy == starty))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty - 1; i >= 0; i--) // sus
	{
		if (board[i][startx] <= 0 && (kingy == i && kingx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	for (int i = startx + 1; i < LENGTH; i++) // spre dreapta
	{
		if (board[starty][i] <= 0 && (kingy == starty && kingx == i))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty + 1; i < LENGTH; i++) // jos
	{
		if (board[i][startx] <= 0 && (kingy == i && kingx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	return 0;
}

int BishopBChess(int startx, int starty, int kingx, int kingy)
{
	int j = startx - 1;
	for (int i = starty - 1; i >= 0; i--) // spre stanga sus
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty - 1; i >= 0; i--) // spre dreapta sus
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = startx - 1;
	for (int i = starty + 1; i <= 7; i++) // spre stanga jos
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty + 1; i <= 7; i++)  // spre dreapta jos
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int QueenBChess(int startx, int starty, int kingx, int kingy)
{
	for (int i = startx - 1; i >= 0; i--) // spre stanga
	{
		if (board[starty][i] <= 0 && (kingx == i && kingy == starty))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty - 1; i >= 0; i--) // sus
	{
		if (board[i][startx] <= 0 && (kingy == i && kingx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	for (int i = startx + 1; i < LENGTH; i++) // spre dreapta
	{
		if (board[starty][i] <= 0 && (kingy == starty && kingx == i))
		{
			return 1;
		}
		else if (board[starty][i] != 0)
		{
			break;
		}
	}
	for (int i = starty + 1; i < LENGTH; i++) // jos
	{
		if (board[i][startx] <= 0 && (kingy == i && kingx == startx))
		{
			return 1;
		}
		else if (board[i][startx] != 0)
		{
			break;
		}
	}
	int j = startx - 1;
	for (int i = starty - 1; i >= 0; i--) // spre stanga sus
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty - 1; i >= 0; i--) // spre dreapta sus
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = startx - 1;
	for (int i = starty + 1; i <= 7; i++) // spre stanga jos
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = startx + 1;
	for (int i = starty + 1; i < LENGTH; i++)  // spre dreapta jos
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int KnightBChess(int startx, int starty, int kingx, int kingy)
{
	if (starty - 2 >= 0 && startx - 1 >= 0 && kingy == starty - 2 && kingx == startx - 1 && board[kingy][kingx] <= 0)
	{
		return 1; // stanga sus
	}
	if (starty - 2 >= 0 && startx + 1 < LENGTH && kingy == starty - 2 && kingx == startx + 1 && board[kingy][kingx] <= 0)
	{
		return 1; // dreapta sus
	}
	if (starty - 1 >= 0 && startx + 2 < LENGTH && kingy == starty - 1 && kingx == startx + 2 && board[kingy][kingx] <= 0)
	{
		return 1; // dreapta 1
	}
	if (starty + 1 >= 0 && startx + 2 < LENGTH && kingy == starty + 1 && kingx == startx + 2 && board[kingy][kingx] <= 0)
	{
		return 1; // dreapta 2
	}
	if (starty + 2 < LENGTH && startx + 1 < LENGTH && kingy == starty + 2 && kingx == startx + 1 && board[kingy][kingx] <= 0)
	{
		return 1; // jos 1
	}
	if (starty + 2 < LENGTH && startx - 1 >= 0 && kingy == starty + 2 && kingx == startx - 1 && board[kingy][kingx] <= 0)
	{
		return 1; //jos 2
	}
	if (starty + 1 < LENGTH && startx - 2 >= 0 && kingy == starty + 1 && kingx == startx - 2 && board[kingy][kingx] <= 0)
	{
		return 1; // stanga 1
	}
	if (starty - 1 >= 0 && startx - 2 >= 0 && kingy == starty - 1 && kingx == startx - 2 && board[kingy][kingx] <= 0)
	{
		return 1;
	}
	return 0;
}

int KingBChess(int startx, int starty, int kingx, int kingy)
{
	if (startx - 1 >= 0 && starty - 1 >= 0 && kingy == starty - 1 && kingx == startx - 1 && board[kingy][kingx] >= 0)
	{
		return 1;
	}
	if (starty - 1 >= 0 && kingx == startx && kingy == starty - 1 && board[kingy][kingx] >= 0)
	{
		return 1;
	}
	if (starty - 1 >= 0 && startx + 1 < LENGTH && kingx == startx + 1 && kingy == starty - 1 && board[kingy][kingx] >= 0)
	{
		return 1;
	}
	if (startx + 1 < LENGTH && kingy == starty && kingx == startx + 1 && board[kingy][kingx] >= 0)
	{
		return 1;
	}
	if (startx + 1 < LENGTH && starty + 1 < LENGTH && kingy == starty + 1 && kingx == startx + 1 && board[kingy][kingx] >= 0)
	{
		return 1;
	}
	if (starty + 1 < LENGTH && kingy == starty + 1 && kingx == startx && board[kingy][kingx] >= 0)
	{
		return 1;
	}
	if (startx - 1 >= 0 && starty + 1 < LENGTH && kingx == startx - 1 && kingy == starty + 1 && board[kingy][kingx] >= 0)
	{
		return 1;
	}
	if (startx - 1 >= 0 && kingy == starty && kingx == startx - 1 && board[kingy][kingx] >= 0)
	{
		return 1;
	}
	return 0;
}



int KingBlackCheck(int posKingx, int posKingy)
{
	int ok = 0;
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < LENGTH; j++)
		{
			if (board[i][j] < 0)
			{
				if (board[i][j] == PawnWHITE)
				{
					ok = PawnWChess(j, i, posKingx, posKingy);
				}
				if (board[i][j] == RookWHITE)
				{
					ok = RookWChess(j, i, posKingx, posKingy);
				}
				if (board[i][j] == KnightWHITE)
				{
					ok = KnightWChess(j, i, posKingx, posKingy);
				}
				if (board[i][j] == BishopWHITE)
				{
					ok = BishopWChess(j, i, posKingx, posKingy);
				}
				if (board[i][j] == QueenWHITE)
				{
					ok = QueenWChess(j, i, posKingx, posKingy);
				}
				if (board[i][j] == KingWHITE)
				{
					ok = KingWChess(j, i, posKingx, posKingy);
				}
				if (ok == 1)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

int KingB(int startx, int starty, int endx, int endy)
{
	if (startx - 1 >= 0 && starty - 1 >= 0 && endy == starty - 1 && endx == startx - 1 && board[endy][endx] <= 0)
	{
		int ok = KingBlackCheck(startx - 1, starty - 1);
		if (ok == 1)
		{
			return 1;  // stanga sus
		}
	}
	if (starty - 1 >= 0 && endx == startx && endy == starty - 1 && board[endy][endx] <= 0)
	{
		int ok = KingBlackCheck(startx, starty - 1);
		if (ok == 1)
		{
			return 1; // sus
		}
	}
	if (starty - 1 >= 0 && startx + 1 < LENGTH && endx == startx + 1 && endy == starty - 1 && board[endy][endx] <= 0)
	{
		int ok = KingBlackCheck(startx + 1, starty - 1);
		if (ok == 1)
		{
			return 1; // dreapta sus
		}
	}
	if (startx + 1 < LENGTH && endy == starty && endx == startx + 1 && board[endy][endx] <= 0)
	{
		int ok = KingBlackCheck(startx + 1, starty);
		if (ok == 1)
		{
			return 1; // dreapta
		}
	}
	if (startx + 1 < LENGTH && starty + 1 < LENGTH && endy == starty + 1 && endx == startx + 1 && board[endy][endx] <= 0)
	{
		int ok = KingBlackCheck(startx + 1, starty + 1);
		if (ok == 1)
		{
			return 1; // dreapta jos
		}
	}
	if (starty + 1 < LENGTH && endy == starty + 1 && endx == startx && board[endy][endx] <= 0)
	{
		int ok = KingBlackCheck(startx, starty + 1);
		if (ok == 1)
		{
			return 1; // jos
		}
	}
	if (startx - 1 >= 0 && starty + 1 < LENGTH && endx == startx - 1 && endy == starty + 1 && board[endy][endx] <= 0)
	{
		int ok = KingBlackCheck(startx - 1, starty + 1);
		if (ok == 1)
		{
			return 1; // stanga jos
		}
	}
	if (startx - 1 >= 0 && endy == starty && endx == startx - 1 && board[endy][endx] <= 0)
	{
		int ok = KingBlackCheck(startx - 1, starty);
		if (ok == 1)
		{
			return 1; // stanga
		}
	}
	// rocada in dreapta
	if (rookBRight == 0 && kingBMove == 0 && board[0][5] == 0 && board[0][6] == 0 && endy == 0 && endx == 6)
	{
		int ok = KingBlackCheck(4, 0);
		if (ok == 1)
		{
			ok = KingBlackCheck(5, 0);
			if (ok == 1)
			{
				ok = KingBlackCheck(6, 0);
				if (ok == 1)
				{
					kingBMove = 1;
					rookBRight = 1;
					board[0][7] = 0;
					board[0][5] = RookBLACK;
					return 1;
				}
			}
		}
	}
	if (rookBLeft == 0 && kingBMove == 0 && board[0][3] == 0 && board[0][2] == 0 && board[0][1] == 0 && endy == 0 && endx == 2)
	{
		int ok = KingBlackCheck(4, 0);
		if (ok == 1)
		{
			ok = KingBlackCheck(3, 0);
			if (ok == 1)
			{
				ok = KingBlackCheck(2, 0);
				if (ok == 1)
				{
					ok = KingBlackCheck(1, 0);
					if (ok == 1)
					{
						kingBMove = 1;
						rookBLeft = 1;
						board[0][0] = 0;
						board[0][3] = RookBLACK;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


int KingWhiteCheck(int posKingx, int posKingy)
{
	int ok = 0;
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < LENGTH; j++)
		{
			if (board[i][j] > 0)
			{
				if (board[i][j] == PawnBLACK)
				{
					ok = PawnBChess(j, i, posKingx, posKingy);
				}
				if (board[i][j] == RookBLACK)
				{
					ok = RookBChess(j, i, posKingx, posKingy);
				}
				if (board[i][j] == KnightBLACK)
				{
					ok = KnightBChess(j, i, posKingx, posKingy);
				}
				if (board[i][j] == BishopBLACK)
				{
					ok = BishopBChess(j, i, posKingx, posKingy);
				}
				if (board[i][j] == QueenBLACK)
				{
					ok = QueenBChess(j, i, posKingx, posKingy);
				}
				if (board[i][j] == KingBLACK)
				{
					ok = KingBChess(j, i, posKingx, posKingy);
				}
				if (ok == 1)
				{
					//	std::cout << "da" << "\n";
					return 0;
				}
			}
		}
	}
	return 1;
}

int KingW(int startx, int starty, int endx, int endy)
{
	if (startx - 1 >= 0 && starty - 1 >= 0 && endy == starty - 1 && endx == startx - 1 && board[endy][endx] >= 0)
	{
		int ok = KingWhiteCheck(startx - 1, starty - 1);
		if (ok == 1)
		{
			return 1;  // stanga sus
		}
	}
	if (starty - 1 >= 0 && endx == startx && endy == starty - 1 && board[endy][endx] >= 0)
	{
		int ok = KingWhiteCheck(startx, starty - 1);
		if (ok == 1)
		{
			return 1; // sus
		}
	}
	if (starty - 1 >= 0 && startx + 1 < LENGTH && endx == startx + 1 && endy == starty - 1 && board[endy][endx] >= 0)
	{
		int ok = KingWhiteCheck(startx + 1, starty - 1);
		if (ok == 1)
		{
			return 1; // dreapta sus
		}
	}
	if (startx + 1 < LENGTH && endy == starty && endx == startx + 1 && board[endy][endx] >= 0)
	{
		int ok = KingWhiteCheck(startx + 1, starty);
		if (ok == 1)
		{
			return 1; // dreapta
		}
	}
	if (startx + 1 < LENGTH && starty + 1 < LENGTH && endy == starty + 1 && endx == startx + 1 && board[endy][endx] >= 0)
	{
		int ok = KingWhiteCheck(startx + 1, starty + 1);
		if (ok == 1)
		{
			return 1; // dreapta jos
		}
	}
	if (starty + 1 < LENGTH && endy == starty + 1 && endx == startx && board[endy][endx] >= 0)
	{
		int ok = KingWhiteCheck(startx, starty + 1);
		if (ok == 1)
		{
			return 1; // jos
		}
	}
	if (startx - 1 >= 0 && starty + 1 < LENGTH && endx == startx - 1 && endy == starty + 1 && board[endy][endx] >= 0)
	{
		int ok = KingWhiteCheck(startx - 1, starty + 1);
		if (ok == 1)
		{
			return 1; // stanga jos
		}
	}
	if (startx - 1 >= 0 && endy == starty && endx == startx - 1 && board[endy][endx] >= 0)
	{
		int ok = KingWhiteCheck(startx - 1, starty);
		if (ok == 1)
		{
			return 1; // stanga
		}
	}
	// rocada in dreapta
	if (kingWMove == 0 && rookWRight == 0 && board[7][5] == 0 && board[7][6] == 0 && endy == 7 && endx == 6)
	{
		int ok = 1;
		ok = KingWhiteCheck(4, 7);
		if (ok == 1)
		{
			ok = KingWhiteCheck(5, 7);
			if (ok == 1)
			{
				ok = KingWhiteCheck(6, 7);
				if (ok == 1)
				{
					board[7][7] = 0;
					board[7][5] = RookWHITE;
					kingWMove = 1;
					rookWRight = 1;
					return 1;
				}
			}
		}
	}
	// rocada in stanga
	if (kingWMove == 0 && rookWRight == 0 && board[7][3] == 0 && board[7][2] == 0 && board[7][1] == 0 && endy == 7 && endx == 2)
	{
		int ok = 1;
		ok = KingWhiteCheck(4, 7);
		if (ok == 1)
		{
			ok = KingWhiteCheck(3, 7);
			if (ok == 1)
			{
				ok = KingWhiteCheck(2, 7);
				if (ok == 1)
				{
					ok = KingWhiteCheck(1, 7);
					if (ok == 1)
					{
						board[7][0] = 0;
						board[7][3] = RookWHITE;
						kingWMove = 1;
						rookWLeft = 1;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


void posKingWhite()
{
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < LENGTH; j++)
		{
			if (board[i][j] == KingWHITE)
			{
				kingWhite.x = j;
				kingWhite.y = i;
				break;
			}
		}
	}
}

void posKingBlack()
{
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < LENGTH; j++)
		{
			if (board[i][j] == KingBLACK)
			{
				kingBlack.y = i;
				kingBlack.x = j;
				break;
			}
		}
	}
}

int main()
{
	RenderWindow window(VideoMode(800, 800), "Chess Engine");
	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

	t1.loadFromFile("images/board.png");
	t2.loadFromFile("images/PionNegru.png");
	t3.loadFromFile("images/PionAlb.png");
	t4.loadFromFile("images/TurnNegru.png");
	t5.loadFromFile("images/TurnAlb.png");
	t6.loadFromFile("images/CalAlb.png");
	t7.loadFromFile("images/CalNegru.png");
	t8.loadFromFile("images/NebunNegru.png");
	t9.loadFromFile("images/NebunAlb.png");
	t10.loadFromFile("images/ReginaAlb.png");
	t11.loadFromFile("images/ReginaNegru.png");
	t12.loadFromFile("images/RegeNegru.png");
	t13.loadFromFile("images/RegeAlb.png");
	t14.loadFromFile("images/TransformareAlb.png");
	t15.loadFromFile("images/TransformareNegru.png");

	Sprite table(t1);
	Sprite PawnBlack(t2);
	Sprite PawnWhite(t3);
	Sprite RookBlack(t4);
	Sprite RookWhite(t5);
	Sprite KnightWhite(t6);
	Sprite KnightBlack(t7);
	Sprite BishopBlack(t8);
	Sprite BishopWhite(t9);
	Sprite QueenWhite(t10);
	Sprite QueenBlack(t11);
	Sprite KingBlack(t12);
	Sprite KingWhite(t13);
	Sprite Mov;
	Sprite WHITETransform(t14);
	Sprite BLACKTransform(t15);

	float dx = 0, dy = 0;
	int numMovdPiece = 0;

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);
		x = pos.x / size;
		y = pos.y / size;
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
			window.clear();
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					//std::cout << "x=" << x << " y=" << y << "\n";
					//std::cout << "pos_x=" << pos.x << " pos_y=" << pos.y << "\n";
					//std::cout << "board[y][x]=" << board[y][x] << "\n";
					//std::cout << "\n";
					if (transformationW == 1)
					{
						if (pos.y >= transformWhite.y * size && pos.y <= (transformWhite.y + 1) * size && pos.x >= transformWhite.x * size && pos.x <= (transformWhite.x + 1) * size)
						{
							int xx = pos.x % 100, yy = pos.y % 100;
							//std::cout << "pos.y=" << yy << "\n";
							//std::cout << "pos.x=" << xx << "\n";
							if (xx < 50 && yy < 50 && xx > 0 && yy > 0)
							{
								board[transformWhite.y][transformWhite.x] = RookWHITE;
								transformationW = 0;
							}
							if (xx > 50 && xx < 100 && yy < 50 && yy > 0)
							{
								board[transformWhite.y][transformWhite.x] = QueenWHITE;
								transformationW = 0;
							}
							if (xx > 50 && xx < 100 && yy>50 && yy < 100)
							{
								board[transformWhite.y][transformWhite.x] = KnightWHITE;
								transformationW = 0;
							}
							if (xx < 50 && xx>0 && yy > 50 && y < 100)
							{
								board[transformWhite.y][transformWhite.x] = BishopWHITE;
								transformationW = 0;
							}
							if (transformationW == 0)
							{
								posKingBlack();
								int h = KingBlackCheck(kingBlack.x, kingBlack.y);
								if (h == 0)
								{
									checkB = 1;
								}
							}
						}
					}
					if (transformationB == 1)
					{
						if (pos.y >= transformBlack.y * size && pos.y <= (transformBlack.y + 1) * size && pos.x >= transformBlack.x * size && pos.x <= (transformBlack.x + 1) * size)
						{
							int xx = pos.x % 100, yy = pos.y % 100;
							//std::cout << "pos.y=" << yy << "\n";
							//std::cout << "pos.x=" << xx << "\n";
							if (xx < 50 && yy < 50 && xx > 0 && yy > 0)
							{
								board[transformBlack.y][transformBlack.x] = RookBLACK;
								transformationB = 0;
							}
							if (xx > 50 && xx < 100 && yy < 50 && yy > 0)
							{
								board[transformBlack.y][transformBlack.x] = QueenBLACK;
								transformationB = 0;
							}
							if (xx > 50 && xx < 100 && yy>50 && yy < 100)
							{
								board[transformBlack.y][transformBlack.x] = KnightBLACK;
								transformationB = 0;
							}
							if (xx < 50 && xx>0 && yy > 50 && y < 100)
							{
								board[transformBlack.y][transformBlack.x] = BishopBLACK;
								transformationB = 0;
							}
							if (transformationB == 0)
							{
								posKingWhite();
								int h = KingWhiteCheck(kingWhite.x, kingWhite.y);
								if (h == 0)
								{
									checkW = 1;
								}
							}
						}
					}
					if (board[y][x] != 0)
					{
						dx = pos.x - x * 100;
						dy = pos.y - y * 100;
						if (board[y][x] == PawnBLACK && moving == 1)
						{
							numMovdPiece = PawnBLACK;
							Mov = PawnBlack;
							board[y][x] = 0;
						}
						if (board[y][x] == PawnWHITE && moving == 0)
						{
							numMovdPiece = PawnWHITE;
							Mov = PawnWhite;
							board[y][x] = 0;
						}
						if (board[y][x] == RookBLACK && moving == 1)
						{
							numMovdPiece = RookBLACK;
							Mov = RookBlack;
							board[y][x] = 0;

						}
						if (board[y][x] == RookWHITE && moving == 0)
						{
							numMovdPiece = RookWHITE;
							Mov = RookWhite;
							board[y][x] = 0;

						}
						if (board[y][x] == KnightWHITE && moving == 0)
						{
							numMovdPiece = KnightWHITE;
							Mov = KnightWhite;
							board[y][x] = 0;
						}
						if (board[y][x] == KnightBLACK && moving == 1)
						{
							numMovdPiece = KnightBLACK;
							Mov = KnightBlack;
							board[y][x] = 0;
						}
						if (board[y][x] == BishopBLACK && moving == 1)
						{
							numMovdPiece = BishopBLACK;
							Mov = BishopBlack;
							board[y][x] = 0;
						}
						if (board[y][x] == BishopWHITE && moving == 0)
						{
							numMovdPiece = BishopWHITE;
							Mov = BishopWhite;
							board[y][x] = 0;
						}
						if (board[y][x] == QueenWHITE && moving == 0)
						{
							numMovdPiece = QueenWHITE;
							Mov = QueenWhite;
							board[y][x] = 0;
						}
						if (board[y][x] == QueenBLACK && moving == 1)
						{
							numMovdPiece = QueenBLACK;
							Mov = QueenBlack;
							board[y][x] = 0;
						}
						if (board[y][x] == KingBLACK && moving == 1)
						{
							numMovdPiece = KingBLACK;
							Mov = KingBlack;
							board[y][x] = 0;
						}
						if (board[y][x] == KingWHITE && moving == 0)
						{
							numMovdPiece = KingWHITE;
							Mov = KingWhite;
							board[y][x] = 0;
						}
						if (board[y][x] == 0)
						{
							move = 1;
							oldPos.x = x;
							oldPos.y = y;
						}
					}
				}
			}
			if (e.type == Event::MouseButtonReleased)
			{
				if (e.key.code == Mouse::Left)
				{
					int ok = 2;
					if (numMovdPiece == PawnWHITE && move == 1)
					{
						ok = PawnW(oldPos.x, oldPos.y, x, y);
					}
					if (numMovdPiece == PawnBLACK && move == 1)
					{
						ok = PawnB(oldPos.x, oldPos.y, x, y);
					}
					if (numMovdPiece == RookWHITE && move == 1)
					{
						ok = RookW(oldPos.x, oldPos.y, x, y);
						if (ok == 1 && rookWLeft == 0 && oldPos.y == 7 && oldPos.x == 0)
						{
							rookWLeft = 1;
							//std::cout << rookWLeft << "\n";
						}
						if (ok == 1 && rookWRight == 0 && oldPos.y == 7 && oldPos.x == 7)
						{
							rookWRight = 1;
							//std::cout << rookWRight << "\n";
						}
					}
					if (numMovdPiece == RookBLACK && move == 1)
					{
						ok = RookB(oldPos.x, oldPos.y, x, y);
						if (ok == 1 && rookBRight == 0 && oldPos.y == 0 && oldPos.x == 7)
						{
							rookBRight = 1;
							//std::cout << rookBRight<< "\n";
						}
						if (ok == 1 && rookBLeft == 0 && oldPos.y == 0 && oldPos.x == 0)
						{
							rookBLeft = 1;
							//std::cout << rookBLeft << "\n";
						}
					}
					if (numMovdPiece == BishopWHITE && move == 1)
					{
						ok = BishopW(oldPos.x, oldPos.y, x, y);
					}
					if (numMovdPiece == BishopBLACK && move == 1)
					{
						ok = BishopB(oldPos.x, oldPos.y, x, y);
					}
					if (numMovdPiece == QueenWHITE && move == 1)
					{
						ok = QueenW(oldPos.x, oldPos.y, x, y);
					}
					if (numMovdPiece == QueenBLACK && move == 1)
					{
						ok = QueenB(oldPos.x, oldPos.y, x, y);
					}
					if (numMovdPiece == KnightWHITE && move == 1)
					{
						ok = KnightW(oldPos.x, oldPos.y, x, y);
					}
					if (numMovdPiece == KnightBLACK && move == 1)
					{
						ok = KnightB(oldPos.x, oldPos.y, x, y);
					}
					if (numMovdPiece == KingBLACK && move == 1)
					{
						ok = KingB(oldPos.x, oldPos.y, x, y);
						if (ok == 1 && kingBMove == 0)
						{
							kingBMove = 1;
							//	std::cout << kingBMove << "\n";
						}
					}
					if (numMovdPiece == KingWHITE && move == 1)
					{
						ok = KingW(oldPos.x, oldPos.y, x, y);
						if (ok == 1 && kingWMove == 0)
						{
							kingWMove = 1;
							//std::cout << "primaMutareREGEalb=" << kingWMove << "\n";
						}
					}
					if (ok == 1)
					{
						int nr = board[y][x];
						board[y][x] = numMovdPiece;
						if (y == 0 && numMovdPiece == PawnWHITE)
						{
							transformationW = 1;
							transformWhite.x = x;
							transformWhite.y = y;
							board[y][x] = 0;
						}
						if (y == 7 && numMovdPiece == PawnBLACK)
						{
							transformationB = 1;
							transformBlack.x = x;
							transformBlack.y = y;
							board[y][x] = 0;
						}
						if (moving == 0) // albul a mutat si urmeaza negrul
						{
							if (checkW == 1)
							{
								posKingWhite();
								int s = KingWhiteCheck(kingWhite.x, kingWhite.y);
								if (s == 0)
								{
									board[oldPos.y][oldPos.x] = numMovdPiece;
									board[y][x] = nr;
								}
								else
								{
									checkW = 0;
									posKingBlack();
									int sah = KingBlackCheck(kingBlack.x, kingBlack.y);
									if (sah == 0)
									{
										checkB = 1;
									}
									moving = 1;
								}
							}
							else
							{
								posKingWhite();
								int sa = KingWhiteCheck(kingWhite.x, kingWhite.y);
								if (sa == 0)
								{
									board[oldPos.y][oldPos.x] = numMovdPiece;
									board[y][x] = nr;
								}
								else
								{
									posKingBlack();
									int sah = KingBlackCheck(kingBlack.x, kingBlack.y);
									if (sah == 0)
									{
										checkB = 1;
									}
									moving = 1;
								}
							}
						}
						else // negrul a mutat si urmeaza albul
						{
							if (checkB == 1)
							{
								posKingBlack();
								int s = KingBlackCheck(kingBlack.x, kingBlack.y);
								if (s == 0)
								{
									board[oldPos.y][oldPos.x] = numMovdPiece;
									board[y][x] = nr;
								}
								else
								{
									checkB = 0;
									posKingWhite();
									int sah = KingWhiteCheck(kingWhite.x, kingWhite.y);
									if (sah == 0)
									{
										checkW = 1;
									}
									moving = 0;
								}
							}
							else
							{
								posKingBlack();
								int sa = KingBlackCheck(kingBlack.x, kingBlack.y);
								if (sa == 0)
								{
									board[oldPos.y][oldPos.x] = numMovdPiece;
									board[y][x] = nr;
								}
								else
								{
									posKingWhite();
									int sah = KingWhiteCheck(kingWhite.x, kingWhite.y);
									if (sah == 0)
									{
										checkW = 1;
									}
									moving = 0;
								}
							}
						}
					}
					else if (ok == 0)
					{
						board[oldPos.y][oldPos.x] = numMovdPiece;
					}
					move = 0;
				}
			}
		}
		// afisare //
		window.clear();
		window.draw(table);
		if (transformationW == 1)
		{
			WHITETransform.setPosition(transformWhite.x * size, transformWhite.y * size);
			window.draw(WHITETransform);
		}
		if (transformationB == 1)
		{
			BLACKTransform.setPosition(transformBlack.x * size, transformBlack.y * size);
			window.draw(BLACKTransform);
		}
		if (move == 1)
		{
			Mov.setPosition(pos.x - dx, pos.y - dy);
			window.draw(Mov);
		}
		for (int i = 0; i < LENGTH; i++)
		{
			for (int j = 0; j < LENGTH; j++)
			{

				if (board[i][j] != 0)
				{
					if (board[i][j] == PawnBLACK)
					{
						PawnBlack.setPosition(j * size, i * size);
						window.draw(PawnBlack);
					}
					if (board[i][j] == PawnWHITE)
					{
						PawnWhite.setPosition(j * size, i * size);
						window.draw(PawnWhite);
					}
					if (board[i][j] == RookBLACK)
					{
						RookBlack.setPosition(j * size, i * size);
						window.draw(RookBlack);

					}
					if (board[i][j] == RookWHITE)
					{
						RookWhite.setPosition(j * size, i * size);
						window.draw(RookWhite);

					}
					if (board[i][j] == KnightWHITE)
					{
						KnightWhite.setPosition(j * size, i * size);
						window.draw(KnightWhite);
					}
					if (board[i][j] == KnightBLACK)
					{
						KnightBlack.setPosition(j * size, i * size);
						window.draw(KnightBlack);
					}
					if (board[i][j] == BishopBLACK)
					{
						BishopBlack.setPosition(j * size, i * size);
						window.draw(BishopBlack);
					}
					if (board[i][j] == BishopWHITE)
					{
						BishopWhite.setPosition(j * size, i * size);
						window.draw(BishopWhite);
					}
					if (board[i][j] == QueenWHITE)
					{
						QueenWhite.setPosition(j * size, i * size);
						window.draw(QueenWhite);
					}
					if (board[i][j] == QueenBLACK)
					{
						QueenBlack.setPosition(j * size, i * size);
						window.draw(QueenBlack);
					}
					if (board[i][j] == KingBLACK)
					{
						KingBlack.setPosition(j * size, i * size);
						window.draw(KingBlack);
					}
					if (board[i][j] == KingWHITE)
					{
						KingWhite.setPosition(j * size, i * size);
						window.draw(KingWhite);
					}
				}
			}
		}
		window.display();
	}
	return 0;
}












































//#include "gui.h"
//#include "ai.h"
//#include "chess.h"
//
//int main() {
//    Board board;
//    AI ai(board); // Pass the Board object to AI
//    Color playerColor = WHITE;  // You can choose the color for the player
//
//    GUI gui;
//    gui.run(board);
//
//    return 0;
//}




//#include <SFML/Graphics.hpp>
//#include "chess.h"
//#include "ai.h"
//
//#include<iostream>
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess Engine");
//    
//    if (!window.isOpen()) {
//        std::cerr << "Failed to create the window." << std::endl;
//        return -1;
//    }
//
//    std::cout << "Window created successfully." << std::endl;
//
//    Chess chessboard;
//    
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        chessboard.render(window);
//        window.display();
//    }
//
//    return 0;
//}
