//===================================
//include guard
#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

//===================================
//included dependencies
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

//a vertex of the maze
class Tile
{
public:
	Tile() {}
	Tile(int X, int Y) { x=X;y=Y; }
	int x;
	int y;
	bool solid;
};

//a class to generate a random maze
class MazeGenerator
{
	int XSize;
	int YSize;
	void DepthFirstSearch(Tile& vertex); //recursive DFS to generate the maze
public:
	vector<vector<Tile>> tiles;
	MazeGenerator(int,int); //Generates a maze given size
	void CutHoleInMiddle(int, int); //Cuts a hole in the maze - space for menu
	void Print();
};

#endif