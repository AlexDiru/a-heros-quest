#include "cls.h"

void ClearScreen::cls() 
{ 
	//positions the cursor to the top left of the cmd prompt so the screen data is overwritten
    COORD coord;
	coord.X = 0;
	coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ClearScreen::fullcls()
{
	system("cls");
}