#include "item.h"

item::item()
{
	this->construct();
}

void item::construct()
{
	healthB = 0;
	attB = 0;
	defB = 0;
	spdB = 0;
	pickedUp = false;
	xPos = -1;
	yPos = -1;
}