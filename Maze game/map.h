//===================================
//include guard
#ifndef MAP_H
#define MAP_H

//===================================
//included dependencies
#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "consoleColour.h"
#include "cls.h"
#include "entity.h"
#include "item.h"

class map : public consoleColour
{
	int xSize, ySize; //tile sizes of the map
	int difficulty; //affects the level of the enemies that will occur
	string name; //name of the map
	WORD entityColour; //foreground of enemies and items rendered on the map
	ClearScreen CLS; //class to clear screen
public:

	int number; //the number of the map

	vector<string> tileData; //line by line for tile data

	void generateData(int,int); //randomly generates data given an x and y size (only takes odd values)
	void loadData(const string&); //loads the map data from a directory
	void loadData(int); //loads the map given the map number

	void renderMap(); //renders just the map with any entities
	void renderMap(const vector<entity>&, const vector<item>&); //renders the map with items and entitys 
	vector<string> getTileData() const { return tileData; } //gets the vector<string> tileData of the map data

	void destroy(); //destroy the map - clears out the vectors and resets the size 

	vector<mapexit> exitList; //stores all the possible exits of a map
	vector<item> itemList; //keeps track of all the items on the map
	vector<entity> enemyList; //keeps track of all the enemies on the map

	string getName() const { return name; } //gets the name of the map
	int getDifficulty() const { return difficulty; } //gets the difficulty of the map

	void printStats(); //prints info about the map

	void moveEnemies(); //moves all the enemies on the map
};



#endif