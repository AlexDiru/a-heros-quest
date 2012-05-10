#include "game.h"

void InsertInString(string &str, const string& ins, int pos)
{
	for (int i=0;i<ins.length();i++)
		str[pos+i] = ins[i];
}

game::game()
{
	saveSlotInUse = -1;
}

int game::MainMenu()
{
	CLS.fullcls();
	int action = -1;
	char userInput;
	printMainMenu();
	bool loopAgain; //whether to loop for userinput
	do
	{
		loopAgain = false;
		userInput = getch();
		switch (tolower(userInput))
		{
		case 'n':
			return 0;
			break;
		case 'l':
			return 1;
			break;
		case 'i':
			return 2;
			break;
		case 'e':
			return 3;
			break;
		default:
			loopAgain = true;
			break;
		}
	} while (loopAgain);
	return -1;
}

int game::NewGameMenu()
{
	CLS.fullcls();
	int action = -1;
	char userInput;
	printNewGameMenu();
	bool loopAgain; //whether to loop for userinput
	do
	{
		loopAgain = false;
		userInput = getch();
		switch (tolower(userInput))
		{
		case 'b':
			return 0;
			break;
		case '1':
			saveSlotInUse = 1;
			return 1;
			break;
		case '2':
			saveSlotInUse = 2;
			return 2;
			break;
		case '3':
			saveSlotInUse = 3;
			return 3;
			break;
		default:
			loopAgain = true;
			break;
		}
	} while (loopAgain);
	return -1;
}

int game::LoadGameMenu()
{
	CLS.fullcls();
	int action = -1;
	char userInput;
	printLoadGameMenu();
	bool loopAgain; //whether to loop for userinput
	do
	{
		loopAgain = false;
		userInput = getch();
		switch (tolower(userInput))
		{
		case 'b':
			return 0;
			break;
		case '1':
			saveSlotInUse = 1;
			return 1;
			break;
		case '2':
			saveSlotInUse = 2;
			return 2;
			break;
		case '3':
			saveSlotInUse = 3;
			return 3;
			break;
		default:
			loopAgain = true;
			break;
		}
	} while (loopAgain);
	return -1;
}

void game::printMainMenu()
{
	//generate maze
	MazeGenerator Maze(51,41);
	Maze.CutHoleInMiddle(22,10);

	//convert maze to string
	vector<string> mazeString;
	for (int i=0;i<Maze.tiles.size();i++)
	{
		string temp;
		for (int j=0;j<Maze.tiles[i].size();j++)
		{
			if (Maze.tiles[i][j].solid)
				temp.push_back('#');
			else
				temp.push_back(' ');
		}
		mazeString.push_back(temp);
	}

	//insert the menu in the maze
	InsertInString(mazeString[17],"A HERO'S QUEST",17);
	InsertInString(mazeString[19],"[n]ew game",17);
	InsertInString(mazeString[20],"[l]oad game",17);
	InsertInString(mazeString[21],"[i]nstructions",17);
	InsertInString(mazeString[22],"[e]xit",17);

	//print maze string
	for (int i=0;i<mazeString.size();i++)
		cout << mazeString[i] << endl;
}

void game::printNewGameMenu()
{
	//generate maze
	MazeGenerator Maze(51,41);
	Maze.CutHoleInMiddle(22,10);

	//convert maze to string
	vector<string> mazeString;
	for (int i=0;i<Maze.tiles.size();i++)
	{
		string temp;
		for (int j=0;j<Maze.tiles[i].size();j++)
		{
			if (Maze.tiles[i][j].solid)
				temp.push_back('#');
			else
				temp.push_back(' ');
		}
		mazeString.push_back(temp);
	}

	//insert the menu in the maze
	InsertInString(mazeString[17],"NEW GAME",17);

	//array to store the levels of each save
	float Levels[3];
	//check which slots are in use
	char buffer[30];
	for (int slot=1;slot <= 3; slot++)
	{
		//check slot
		string slotText = "Slot ["; 
		slotText += itoa(slot,buffer,10);
		slotText += "] - ";

		string dir = "Saves/slot";
		dir += itoa(slot,buffer,10);
		dir += ".txt";
		ifstream file(dir);

		if (file)
		{
			//it exists
			string name;
			getline(file,name);

			//check empty save slot
			if (name.compare("") == 0)
			{
				slotText += "Empty";
				Levels[slot-1] = 0;
			}
			else
			{
				string level;
				getline(file,level);
				slotText += name;
				slotText += " L";
				slotText += level;
				Levels[slot-1] = atoi(level.c_str());
			}
		}
		else
			throw FileMissingEx();

		InsertInString(mazeString[18+slot],slotText,17);

		file.close();
	}
	string levelText = "Average Level: ";
	levelText += itoa(round(getAverage(Levels,3)),buffer,10);
	InsertInString(mazeString[22],levelText,17);
	InsertInString(mazeString[23],"[b]ack",17);

	//print maze string
	for (int i=0;i<mazeString.size();i++)
		cout << mazeString[i] << endl;
}

void game::printLoadGameMenu()
{
	//generate maze
	MazeGenerator Maze(51,41);
	Maze.CutHoleInMiddle(22,10);

	//convert maze to string
	vector<string> mazeString;
	for (int i=0;i<Maze.tiles.size();i++)
	{
		string temp;
		for (int j=0;j<Maze.tiles[i].size();j++)
		{
			if (Maze.tiles[i][j].solid)
				temp.push_back('#');
			else
				temp.push_back(' ');
		}
		mazeString.push_back(temp);
	}

	//insert the menu in the maze
	InsertInString(mazeString[17],"LOAD GAME",17);

	//array to store the levels of each save
	float Levels[3];
	//check which slots are in use
	char buffer[30];
	for (int slot=1;slot <= 3; slot++)
	{
		//check slot
		string slotText = "Slot ["; 
		slotText += itoa(slot,buffer,10);
		slotText += "] - ";

		string dir = "Saves/slot";
		dir += itoa(slot,buffer,10);
		dir += ".txt";
		ifstream file(dir);

		if (file)
		{
			//it exists
			string name;
			getline(file,name);

			//check empty save slot
			if (name.compare("") == 0)
			{
				slotText += "Empty";
				Levels[slot-1] = 0;
			}
			else
			{
				string level;
				getline(file,level);
				slotText += name;
				slotText += " L";
				slotText += level;
				Levels[slot-1] = atoi(level.c_str());
			}
		}
		else
			throw FileMissingEx();

		InsertInString(mazeString[18+slot],slotText,17);

		file.close();
	}
	string levelText = "Average Level: ";
	levelText += itoa(round(getAverage(Levels,3)),buffer,10);
	InsertInString(mazeString[22],levelText,17);
	InsertInString(mazeString[23],"[b]ack",17);

	//print maze string
	for (int i=0;i<mazeString.size();i++)
		cout << mazeString[i] << endl;
}

void game::printInstructionsMenu()
{
	CLS.fullcls();
	//instructions need to be word wrapped
	string instructions = "";

	instructions += "INSTRUCTIONS\n\n";
	instructions += "You are the player denoted by '%', you must travel around \nthe world in a quest power. Many obstacles will await you:\n\n";
	instructions += "Mazes - Apart from the fields, everything in this world is \npretty much a maze, it's very easy to get lost.\n\n";
	instructions += "Enemies - Spread throughout these mazes are enemies, \ndenoted by '@', if you come into with an enemy they \nwill try to kill you, you must fight back.\n\n";
	instructions += "Items\n\t+ increase the player's health by 10%\n\t^ increase the player's attack by 1\n\tD increase the player's defense by 1\n\tS increase the player's speed by 1\n\n";
	instructions += "Controls\n\tW move up, S move down, A move left, D move right\n\tEsc exit game\n\tR return to main menu\n\n";
	instructions += "Cheats/Debug Mode\n\tQ increase the player's experience by 1000\n\n";
	instructions += "******************************************************\n\n";
	instructions += "Credits\n\tAlexander Spedding\n\n";
	instructions += "******************************************************\n\n";
	instructions += "Press any key to go back to the main menu\n\n";

	cout << instructions << endl;

}