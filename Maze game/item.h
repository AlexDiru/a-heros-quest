//===================================
//include guard
#ifndef ITEM_H
#define ITEM_H

//===================================
//included dependencies
#include "sprite.h"

class item : public sprite
{
public:
	item(); //constructor sets all values to default
	void construct(); //does the same as the construct, but can be called anywhen in the object's lifespan

	int healthB; //bonus to health (in percent)
	int attB; //bonus to attack
	int defB; //bonus to defense
	int spdB; //bonus to speed
	bool pickedUp; //if the item was picked up
	int xPos,yPos; //position of the item
};

#endif