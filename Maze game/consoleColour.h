//===================================
//include guard
#ifndef CONSOLECOLOUR_H
#define CONSOLECOLOUR_H

//===================================
//included dependencies
#include <Windows.h>

//a class to store colour details for the console
class consoleColour
{
protected:
	WORD foregroundColour; //the colour of the map foreground
	WORD backgroundColour; //the colour of the map background
public:
	void setColour(WORD, WORD); //sets the colour variables of the class
	WORD getBackgroundColour() const; //gets the bg colour
	WORD getForegroundColour() const; //gets the fg colour
};

#endif