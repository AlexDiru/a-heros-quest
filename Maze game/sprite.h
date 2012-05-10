//===================================
//include guard
#ifndef SPRITE_H
#define SPRITE_H

//===================================
//included dependencies
#include "consoleColour.h"

//a class to store a sprite - many classes inherit this
//store basic things such as sprite image and position
class sprite : public consoleColour
{
protected:
	char _sprite; //image of sprite
	int xPos, yPos; //position of sprite
public:
	char getSprite() const { return _sprite; } //returns the character of the sprite
	void setSprite(char spr) { _sprite = spr; } //sets the character of the sprite
	void setPosition(int x, int y) { xPos=x; yPos = y; } //sets the position given values
	int getXPos() const { return xPos; } //gets the x position of the sprite
	int getYPos() const { return yPos; } //gets the y position of the sprite
};

#endif