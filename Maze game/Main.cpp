#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include <ctime>
#include <fstream>
using namespace std;

#include "cls.h"
#include "fileexception.h"
#include "formatInputCommand.h"
#include "consoleColour.h"
#include "sprite.h"
#include "item.h"
#include "mapexit.h"
#include "entity.h"
#include "map.h"
#include "game.h"

HANDLE hCurrentProcess = GetCurrentProcess();

int main()
{
	SetPriorityClass(hCurrentProcess, HIGH_PRIORITY_CLASS); //set the game to top priority
	ShowWindow( GetConsoleWindow() , SW_MAXIMIZE); //maxmise console window on start
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); //set default colour

	srand(time(NULL));
	char userInput = ' ';

	ClearScreen CLS;

	//MAIN MENU
	game Game;
	MainMenu:
	int action = Game.MainMenu();

	entity player;
	map Map;

	if (action == 0) //new game menu
	{
		NewGameMenu:
		int saveSlot;
		saveSlot = Game.NewGameMenu();
		if (saveSlot == 0) //go back
			goto MainMenu;
		else
		{
			//new game
			cout << "Are you sure you want to use Slot " << saveSlot << "? [y]/[n]" << endl;
			userInput = getch();
			if (userInput == 'y')
			{
				cout << "Enter your name: " << endl;
				string temp = "";

				//while no entry
				//keep reading input
				while (temp.compare("")==0 || temp.compare(" ")==0)
					getline(cin,temp);

				player.setName(temp);
				//default stats
				Map.number = 1;
				player.setPosition(1,1);
				player.experience = 0;
				player.level = 1;
				player.speed = 6;
				player.attack = 6;
				player.defense = 6;
				player.maxHealth = 20;
				player.currentHealth = 20;
			}
			else goto NewGameMenu;
		}
	}
	else if (action == 1) //load game menu
	{
		LoadGameMenu:
		int saveSlot;
		saveSlot = Game.LoadGameMenu();
		if (saveSlot == 0) //go back
			goto MainMenu;
		else
		{
			Map.number = player.loadData(saveSlot); //load player
			if (Map.number == -1)
				goto LoadGameMenu;
			player.nextLevelExperience = player.getLevelExperience(player.level+1); //show the exp required for the next level
		}
	}
	else if (action == 2) //instructions
	{
		Game.printInstructionsMenu();
		getch();
		goto MainMenu;
	}
	else if (action == 3) //exit game
		return 0;


	//setup the player
	player.setColour(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, BACKGROUND_GREEN);
	player.setSprite('%');

	Map.loadData(Map.number); //load map

	//GAME LOOP
	system("cls");

	while (1)
	{
		bool hasPlayerMoved = false; //if the player collides with a wall when they move this stays false

		CLS.cls();

		//create entity list to be displayed on map
		vector<entity> entityList;
		entityList.push_back(player);
		for (int i=0;i<Map.enemyList.size();i++)
			entityList.push_back(Map.enemyList[i]); //push back enemies

		//check for any deaths of entities
		for (int i=0;i<entityList.size();i++)
		{
			entityList[i].checkDeath();
			if (entityList[i].getDead())
				entityList.erase(entityList.begin() + i--); //if the entity is dead, remove it
		}

		//check for player death
		player.checkDeath();
		if (player.getDead())
		{
			CLS.fullcls();
			cout << "You have died!\n";
			cout << "Enter a character and press return to go to\n";
			cout << "the main menu\n";
			cin.get();
			goto MainMenu;
		}

		Map.renderMap(entityList,Map.itemList);
		Map.printStats();
		player.monitorHealth(); //make sure the player's health is correct
		player.printStats();

		//erase entity list for next loop
		entityList.clear();

		//read user input
		userInput = getch(); //non-standard but no alternative
		
		if (userInput == 'q') 
		{
			player.experience+=1000;
			player.checkIfNextLevel();
		}
		
		//check r press for return to main menu
		//make use of the already in place goto
		if (userInput == 'r')
			goto MainMenu;

		//check escape pressed for end game
		if (userInput == 27)
			return 0;

		//check user input
		vector<string> test(Map.getTileData());
		hasPlayerMoved = player.moveAccordingToUserInput(userInput,test);
		
		player.checkBattles(Map.enemyList); //check for battles after the player has moved
		Map.moveEnemies();
		player.checkBattles(Map.enemyList); //check for battles after the enemy has moved

		player.checkItemCollision(Map.itemList); //check if any items have been picked up

		//load new map if needed
		if (hasPlayerMoved) //make sure the player has moved
		{
			int newmap = player.checkGoToNextMapCollision(Map.exitList); 
			if (newmap != -1)
			{
				int prevMap = Map.number;
				Map.destroy();
				Map.number = newmap;
				CLS.cls();
				char buffer[10];
				string newDirectory = "Maps/map";
				newDirectory.append(itoa(newmap,buffer,10));
				newDirectory += ".txt";
				Map.loadData(newDirectory);
				//set the player's position to the correspond exit gate on the new map
				for (int i=0;i<Map.exitList.size();i++)
				{
					if (Map.exitList[i].goToLevel == prevMap)
					{
						player.setPosition(Map.exitList[i].xPos,Map.exitList[i].yPos);
					}
				}
				//save the game
				player.saveData(Game.saveSlotInUse,Map.number);
			}
		}
	}

	return 0;
}