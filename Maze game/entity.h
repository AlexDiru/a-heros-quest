//===================================
//include guard
#ifndef ENTITY_H
#define ENTITY_H

//===================================
//included dependencies
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "sprite.h"
#include "item.h"
#include "mapexit.h"
#include "fileexception.h"
#include "consoleColour.h"
using namespace std;

class entity : public sprite
{
	bool isDead; //whether the entity is alive or not
	string name; //the entity's name
public:
	//stats - public due to not seeing any point in create a get and a set function for each variable
	int currentHealth,maxHealth; //current health and maxhealth of the entity
	int attack,defense,level,speed; //stats of the entity
	int experience; //experience points of the entity

	entity(); //constructor - sets isdead to false, and sets the experience they require

	bool isCollisionUp(const vector<string>&); //checks for a collision above the entity
	bool isCollisionDown(const vector<string>&); //checks for a collision below the entity
	bool isCollisionLeft(const vector<string>&); //checks for a collision at the left of the entity
	bool isCollisionRight(const vector<string>&); //checks for a collision at the right of the entity

	void moveUp() { this->yPos--; } //moves the entity one tile up
	void moveDown() { this->yPos++; } //moves the entity one tile down
	void moveLeft() { this->xPos--; } //moves the entity one tile left
	void moveRight() { this->xPos++; } //moves the entity one tile right
	bool moveAccordingToUserInput(char, const vector<string>&); //moves the player with the given user input, returns false if there is a collision and the player hasn't moved

	void aiMoveRandomly(const vector<string>& ); //the entity moves in a random direction

	void battle(entity&); //calculates damage between two entities
	void checkDeath(); //checks if the entity is dead, and if so sets their death variable to true
	bool getDead() const { return isDead; }
	void setDead() { isDead = true; }

	void giveRandomStats(int); //gives the entity random stats given the difficulty
	void printStats(); //prints the stats of the entity (used for player)

	void setName(const string& n) { name=n; } //sets the name of the entity
	string getName() const { return name; } //returns the name of the entity

	int nextLevelExperience; //saves doing a for loop each game loop
	int getLevelExperience(int lvl); //gets the experience the entity requires for the next level
	void checkIfNextLevel(); //checks if the entity has enough experience to advance to the next level
	void advanceToNextLevel(); //increases the level variable and also increases stats

	void monitorHealth(); //stops the entity's health from becoming larger than their maxhealth
	void checkItemCollision(vector<item>&); //checks if the player has collided with an item, if so sets the item to picked up and applies the bonus
	int checkGoToNextMapCollision(const vector<mapexit>&); //returns -1 if no map transition is needed, else returns the number of the map to transition to

	void checkBattles(vector<entity>&); //checks all possible battles with enemies for the entity

	void saveData(int,int); //saves the player's data to a file (save slot)
	int loadData(int); //loads the data from the specified slots, returns the map number
};

#endif