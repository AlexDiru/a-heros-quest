#include "mazegenerator.h"

void MazeGenerator::CutHoleInMiddle(int Width, int Height)
{
	for (int y=this->YSize/2-Height/2; y<=this->YSize/2+Height/2; y++)
		for (int x=this->XSize/2-Width/2; x<=this->XSize/2+Width/2; x++)
			this->tiles[y][x].solid = false;
}

void MazeGenerator::DepthFirstSearch(Tile& vertex)
{
	//remove this tile
	vertex.solid = false;

	//error check - otherwise vector range may be oob
	if (vertex.x < 0 || vertex.x >= this->XSize || vertex.y < 0 || vertex.y >= this->YSize)
		return;
	
	//pick a random direction
	int d = rand()%4;
	//variable to make sure all directions have been checked
	int count = 0;

	switch (d)
	{
	case 0:
		case0:
		//e
		if (vertex.x - 2 > 0)
			if (tiles[vertex.y][vertex.x-2].solid)
			{
			
				tiles[vertex.y][vertex.x-1].solid = false;
				DepthFirstSearch(tiles[vertex.y][vertex.x-2]);
			}
		count++;
		if (count > 3) break;

	case 1:
		//w
		if (vertex.x + 2 < this->XSize-1)
			if (tiles[vertex.y][vertex.x+2].solid)
			{
				tiles[vertex.y][vertex.x+1].solid = false;
				DepthFirstSearch(tiles[vertex.y][vertex.x+2]);
			}
		count++;
		if (count > 5) break;

	case 2:
		//n
		if (vertex.y - 2 > 0)
			if (tiles[vertex.y-2][vertex.x].solid)
			{
				tiles[vertex.y-1][vertex.x].solid = false;
				DepthFirstSearch(tiles[vertex.y-2][vertex.x]);
			}
		count++;
		if (count > 3) break;

	case 3:
		//s
		if (vertex.y + 2 < this->YSize-1)
			if (tiles[vertex.y+2][vertex.x].solid)
			{
				tiles[vertex.y+1][vertex.x].solid = false;
				DepthFirstSearch(tiles[vertex.y+2][vertex.x]);
			}
		count++;
		if (count > 3) break;
		goto case0;
	}

}

int nearestOdd(int n, int minval, int maxval)
{
	if ((n/2)*2 != n)
		return n;
	else 
	{
		if (n-1 < minval)
			return n+1;
		else
			return n-1;
	}
}

MazeGenerator::MazeGenerator(int xs, int ys)
{
	//Setup the maze tiles vector
	for (int i=0;i<ys;i++)
	{
		vector<Tile> tvec;
		for (int j=0;j<xs;j++)
		{
			Tile temptile;
			temptile.x = j;
			temptile.y = i;
			temptile.solid = true;
			tvec.push_back(temptile);
		}
		tiles.push_back(tvec);
	}

	//Random odd current cell
	Tile currentCell(nearestOdd(rand()%(xs-2)+1,1,ys-1),nearestOdd(rand()%(ys-2)+1,1,ys-1));
	this->XSize = xs;
	this->YSize = ys;
	DepthFirstSearch(currentCell);
}

void MazeGenerator::Print()
{
	for (int y=0;y<tiles.size();y++)
	{
		for (int x=0;x<tiles[y].size();x++)
		{
			if (tiles[y][x].solid)
				cout << "#";
			else cout << " ";
		}
		cout << endl;
	}
}