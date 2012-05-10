//===================================
//include guard
#ifndef GAME_H
#define GAME_H

//===================================
//included dependencies
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include "mazegenerator.h"
#include "cls.h"
#include "numericfunctions.h"
#include "fileexception.h"
using namespace std;

//function to insert a string in another string (inserts ins in str at pos)
void InsertInString(string &str, const string& ins, int pos);

//this class provides functions to save the player's data and display menus
class game
{
	ClearScreen CLS;
public:
	int saveSlotInUse;

	game(); //constructor - sets saveSlotInUse to -1

	int MainMenu(); //manages the main menu and returns the action of the user
					// -1 = error , 0 = new game, 1 = load game
	int NewGameMenu(); //manages the new games menu and returns the action of the user
					   // 0 = back, 1 = slot 1, 2 = slot 2, 3 = slot 3
	int LoadGameMenu(); //manages the load game menu and returns the action of the user
					   // 0 = back, 1 = slot 1, 2 = slot 2, 3 = slot 3

	void printMainMenu(); //prints the main menu
	void printNewGameMenu(); //prints the new game menu
	void printLoadGameMenu(); //prints the new game menu
	void printInstructionsMenu(); //prints the instructions
};

#endif