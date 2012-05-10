#include "consoleColour.h"

void consoleColour::setColour(WORD fcol, WORD bcol)
{
	this->foregroundColour = fcol; 
	this->backgroundColour = bcol;
}

WORD consoleColour::getBackgroundColour() const 
{ 
	return backgroundColour; 
}

WORD consoleColour::getForegroundColour() const 
{ 
	return foregroundColour; 
}