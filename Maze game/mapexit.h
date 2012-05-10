//===================================
//include guard
#ifndef MAPEXIT_H
#define MAPEXIT_H

//a class that stores data for an exit of a map
class mapexit
{
public:
	int xPos,yPos; //coordinates of the exit
	int goToLevel; //the map number which the exit corresponds to
};

#endif