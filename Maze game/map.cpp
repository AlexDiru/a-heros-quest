#include "map.h"

void map::printStats()
{
	//reset colour to white on black
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED);

	//blank spaces will need to be printed to clear the screen (rewrite over it)
	cout << "Map name: " << name << "               " << endl;
	cout << "Map difficulty: " << difficulty << " / Rec. Level: ";
	
	//print the recommended level the player should be for the map (dependent on the map's difficulty)
	if (difficulty == 0)
		cout << "1";
	else if (difficulty == 1)
		cout << "4";
	else if (difficulty == 2)
		cout << "12";
	else 
		cout << "20";
	cout << "    " << endl;
}

void map::destroy()
{
	//clear all the vectors
	tileData.clear();
	exitList.clear();
	enemyList.clear();
	itemList.clear();

	//set the size to default
	xSize = -1;
	ySize = -1;

	//completely wipe the screen
	CLS.fullcls();
}

void map::loadData(int mapNumber)
{
	//make directory using the given map number
	char buffer[30];
	string directory = "Maps/map";
	directory += itoa(mapNumber,buffer,10);
	directory += ".txt";

	//load data from the created directory
	loadData(directory);
}

void map::loadData(const string& directory)
{
	//open the file fore reading
	ifstream file;
	file.open(directory);

	if (!file)
		throw FileMissingEx();

	//read the map type
	string type;
	getline(file,type);

	//set map colours according to the map type
	if (type.compare("Field") == 0)
	{
		this->setColour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED, BACKGROUND_GREEN );
		this->entityColour = FOREGROUND_RED | FOREGROUND_INTENSITY;
	}
	else if (type.compare("Cave") == 0)
	{
		this->setColour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED, BACKGROUND_RED);
		this->entityColour = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	}
	else if (type.compare("Forest") == 0)
	{
		this->setColour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED, BACKGROUND_GREEN);
		this->entityColour = FOREGROUND_RED | FOREGROUND_INTENSITY;
	}
	else if (type.compare("Castle") == 0)
	{
		this->setColour(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY, BACKGROUND_RED | BACKGROUND_INTENSITY);
		this->entityColour = 0;
	}
	else if (type.compare("Underworld") == 0)
	{
		this->setColour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED,0);
		this->entityColour = FOREGROUND_INTENSITY | FOREGROUND_RED;
	}

	//read the map name
	getline(file,this->name);

	//read map difficulty
	getline(file,type);
	this->difficulty = atoi(type.c_str());

	//parse characters of the file
	int maxFileCol = -1;
	int fileCol = 0; //width of the file
	int fileRow = 0; //height of file
	string blank = ""; //blank string
	this->tileData.push_back(blank.c_str()); //insert a blank string
	char parser; //extract characters from the file
	int numExits=0; //the number of exits the map has
	bool stopReadingMap = false; //tells the program when to stop reading the map data
	item titem; //temp item
	entity tentity; //temp entity

	//read the map file character by character
	while (!stopReadingMap)
	{
		parser = file.get();
		
		switch (parser)
		{
		case '#': //wall
			this->tileData[fileRow].push_back(parser);
			break;

		case '\n': //end of line
			fileRow++;
			this->tileData.push_back(blank.c_str()); //insert a blank string
			//check max width of the file
			if (fileCol > maxFileCol)
				maxFileCol = fileCol;
			fileCol = 0;
			break;

		case 'o':case'O': //exit
			numExits++;
			mapexit temp;
			temp.xPos = fileCol-1;
			temp.yPos = fileRow;
			this->exitList.push_back(temp);
			//don't know the exit yet - they are listed below the map
			this->tileData[fileRow].push_back(parser);
			break;

		case '+': //health
			titem.construct(); //reset item
			titem.setColour(this->entityColour,this->backgroundColour);
			titem.healthB = 10;
			titem.setSprite('+');
			titem.xPos = fileCol-1;
			titem.yPos = fileRow;
			this->itemList.push_back(titem);
			this->tileData[fileRow].push_back(' ');
			break;

		case '^': //attack
			titem.construct(); //reset item
			titem.setColour(this->entityColour,this->backgroundColour);
			titem.attB = 1;
			titem.setSprite('^');
			titem.xPos = fileCol-1;
			titem.yPos = fileRow;
			this->itemList.push_back(titem);
			this->tileData[fileRow].push_back(' ');
			break;

		case 'D': //defense
			titem.construct(); //reset item
			titem.setColour(this->entityColour,this->backgroundColour);
			titem.defB = 1;
			titem.setSprite('D');
			titem.xPos = fileCol-1;
			titem.yPos = fileRow;
			this->itemList.push_back(titem);
			this->tileData[fileRow].push_back(' ');
			break;

		case 'S': //speed
			titem.construct(); //reset item
			titem.setColour(this->entityColour,this->backgroundColour);
			titem.spdB = 1;
			titem.setSprite('S');
			titem.xPos = fileCol-1;
			titem.yPos = fileRow;
			this->itemList.push_back(titem);
			this->tileData[fileRow].push_back(' ');
			break;

		case '@': //enemy
			tentity.setColour(this->entityColour,this->backgroundColour);
			tentity.setPosition(fileCol-1,fileRow);
			tentity.giveRandomStats(this->difficulty);
			tentity.setSprite('@');
			tentity.level = 1+(this->difficulty-1)*4;
			this->enemyList.push_back(tentity);
			this->tileData[fileRow].push_back(' ');
			break;

		case ' ': //empty space
			this->tileData[fileRow].push_back(parser);
			break;

		case '?':
			stopReadingMap = true;
			break;

		default:
			break;
		}

		fileCol++;
	}

	//find out which exits correspond to which levels
	string nothing;
	getline(file,nothing);
	for (int i=0;i<numExits;i++)
	{
		string temp;
		getline(file,temp);
		this->exitList[i].goToLevel = atoi(temp.c_str());
	}

	file.close();

	xSize = fileCol;
	ySize = fileRow;
}

void map::renderMap()
{
	for (int i=0;i<this->tileData.size();i++)
		cout << this->tileData[i] << endl;
}

void map::renderMap(const vector<entity>& eList, const vector<item>& iList)
{
	//create a temp vector as to not overwrite the basic map data
	vector<string> tempData; //cloning the vector caused an exception
	for (int i=0;i<tileData.size();i++)
		tempData.push_back(tileData[i]);

	//generate a 2d array to store the map's colour, as the entitys and items are different colours to the map
	WORD **mapColour = new WORD*[tempData.size()];
	for (int i=0;i<tempData.size();i++)
	{
		mapColour[i] = new WORD[xSize];
		for (int j=0;j<xSize;j++)
		{
			//set default colours
			mapColour[i][j] = this->foregroundColour | this->backgroundColour;
		}
	}

	//need to insert both vectors' data to the map
	for (int i=0;i<eList.size();i++)
	{
		tempData[eList[i].getYPos()][eList[i].getXPos()] = eList[i].getSprite();
		//set new map colour
		mapColour[eList[i].getYPos()][eList[i].getXPos()] = eList[i].getForegroundColour() | this->backgroundColour;
	}

	//items
	for (int i=0;i<iList.size();i++)
	{
		if (!iList[i].pickedUp) //item hasn't been picked up
		{
			//add the item to be rendered
			tempData[iList[i].yPos][iList[i].xPos] = iList[i].getSprite();
			//set colour
			mapColour[iList[i].yPos][iList[i].xPos] = iList[i].getBackgroundColour() | iList[i].getForegroundColour();
		}
	}

	//render map
	for (int i=0;i<tempData.size();i++) //cycle through strings
	{
		for (int j=0;j<tempData[i].length();j++) //cycle through chars
		{
			//set the colour
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),mapColour[i][j]);
			//print the character
			cout << tempData[i][j];
		}
		cout << endl;
	}

	//delete memory
	for (int i=0;i<tempData.size();i++)
		delete[] mapColour[i];
	delete[] mapColour;
}

void map::moveEnemies()
{
	for (int i=0;i<enemyList.size();i++) 
		enemyList[i].aiMoveRandomly(getTileData());
}