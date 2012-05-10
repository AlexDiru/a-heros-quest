//===================================
//include guard
#ifndef CLS_H
#define CLS_H

//===================================
//included dependencies
#include <Windows.h>

class ClearScreen
{
public:
	void cls(); //resets cursor position
	void fullcls(); //wipes entire screen
};

#endif