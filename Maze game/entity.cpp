#include "entity.h"

entity::entity()
{
	isDead = false; 
	nextLevelExperience = getLevelExperience(2);
}

bool entity::isCollisionUp(const vector<string>& tileData)
{
	return !(tileData[this->yPos-1][this->xPos] == ' ' || tileData[this->yPos-1][this->xPos] == 'o'); //space character is empty space
}

bool entity::isCollisionDown(const vector<string>& tileData)
{
	return !(tileData[this->yPos+1][this->xPos] == ' ' | tileData[this->yPos+1][this->xPos] == 'o'); //space character is empty space
}

bool entity::isCollisionLeft(const vector<string>& tileData)
{
	return !(tileData[this->yPos][this->xPos-1] == ' ' | tileData[this->yPos][this->xPos-1] == 'o'); //space character is empty space
}

bool entity::isCollisionRight(const vector<string>& tileData)
{
	return !(tileData[this->yPos][this->xPos+1] == ' ' | tileData[this->yPos][this->xPos+1] == 'o'); //space character is empty space
}

bool entity::moveAccordingToUserInput(char userInput, const vector<string>& tileData)
{
	//up
	if (userInput == 72 || tolower(userInput) == 'w') 
		if (!isCollisionUp(tileData))
		{
			moveUp();
			return true;
		}

	//down
	if (userInput == 80 || tolower(userInput) == 's') 
		if (!isCollisionDown(tileData))
		{
			moveDown();
			return true;
		}

	//left
	if (userInput == 75 || tolower(userInput) == 'a') 
		if (!isCollisionLeft(tileData))
		{
			moveLeft();
			return true;
		}

	//right
	if (userInput == 77 || tolower(userInput) == 'd') 
		if (!isCollisionRight(tileData))
		{
			moveRight();
			return true;
		}

	return false;
}

void entity::aiMoveRandomly(const vector<string>& tileData)
{
	int move = rand()%3; //1 in 3 chance of moving
	if (move == 1)
	{
		//choose a random direction to move in
		unsigned char direction = rand()%4;

		//if the entity can't move a certain direction, then move onto the next direction
		int directionsTested = 0; //the number of directions the entity has tried to move
		switch (direction)
		{
		case 0: //up
			startCase:
			if (!isCollisionUp(tileData))
			{
				moveUp();
				break;
			}
			else directionsTested++;
			if (directionsTested > 3) break;

		case 1: //down
			if (!isCollisionDown(tileData))
			{
				moveDown();
				break;
			}
			else directionsTested++;
			if (directionsTested > 3) break;

		case 2: //left
			if (!isCollisionLeft(tileData))
			{
				moveLeft();
				break;
			}
			else directionsTested++;
			if (directionsTested > 3) break;

		case 3: //right
			if (!isCollisionRight(tileData))
			{
				moveRight();
				break;
			}
			else directionsTested++;
			if (directionsTested > 3) break;

			default:
				goto startCase;
		}
	}
}

void entity::printStats()
{
	//reset colour to white on black
	//blank spaces will need to be printed to clear the screen
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << endl;
	cout << this->name << endl;
	cout << "************                                 " << endl;
	cout << "Level: " << this->level << "                       " << endl;
	cout << "Exp: " << this->experience << "/" << this->nextLevelExperience << "                       " << endl;
	cout << "Health: " << this->currentHealth << "/" << this->maxHealth << "                       " << endl;
	cout << "Atk: " << this->attack << "                       " << endl;
	cout << "Def: " << this->defense << "                       " << endl;
	cout << "Spd: " << this->speed << "                       " << endl;
}

void entity::battle(entity& enemy)
{
	if (!this->isDead && !enemy.isDead)
	{
		//calculate base damage
		int enemyDamage = ((this->attack*2 - enemy.defense) + (rand()%((int)(0.5*this->attack)) - (0.5*this->attack)));
		int playerDamage = ((enemy.attack*2 - this->defense) + (rand()%((int)(0.5*enemy.attack)) - (0.5*enemy.attack)));

		//make sure no negative damage
		if (enemyDamage < 1) enemyDamage = rand()%1;
		if (playerDamage < 1) playerDamage = rand()%1;

		if (enemy.speed > this->speed)
		{
			this->currentHealth -= playerDamage;
			if (this->currentHealth > 0)
				enemy.currentHealth -= enemyDamage;
		}
		else
		{
			enemy.currentHealth -= enemyDamage;
			if (enemy.currentHealth > 0)
				this->currentHealth -= playerDamage;
			else
			{
				//give the player experience
				this->experience += (enemy.attack+enemy.defense+enemy.level+enemy.defense)*6;
				enemy.setDead(); //make sure the enemy is dead
				return; //make sure no chance of giving exp twice
			}
		}
	}
}

void entity::checkDeath()
{
	if (this->currentHealth < 1) 
		this->isDead = true; 
} 

int entity::getLevelExperience(int lvl) 
{ 
	return 8*(lvl+1)*(lvl+1)*(lvl+1);
}

void entity::checkIfNextLevel()
{ 
	if (this->experience >= nextLevelExperience) 
	{ 
		this->advanceToNextLevel();
	}
}

void entity::advanceToNextLevel()
{
	this->level++; 
	this->nextLevelExperience = this->getLevelExperience(this->level+1);
	//increase stats
	this->maxHealth += 5 + rand()%3;
	this->attack += rand()%3 +1;
	this->defense += rand()%3 +1;
	this->speed += rand()%3 +1;
	this->currentHealth = this->maxHealth; //restore health
}

int entity::checkGoToNextMapCollision(const vector<mapexit>& me)
{
	typedef vector<mapexit>::size_type sz;

	for (sz i=0;i<me.size();i++)
		if (me[i].xPos == this->xPos)
			if (me[i].yPos == this->yPos)
				return me[i].goToLevel;

	return -1;
}

void entity::checkItemCollision(vector<item>& im)
{
	for (int i=0;i<im.size();i++)
	{
		if (!im[i].pickedUp)
		{
			if (this->xPos == im[i].xPos)
			{
				if (this->yPos == im[i].yPos)
				{
					//collided
					//set item
					im[i].pickedUp = true;
					//apply bonus
					if (im[i].healthB != 0) //health
						this->currentHealth += (float)(im[i].healthB)/(float)(100) * (float)(this->maxHealth); //healthB% increase
					if (im[i].attB != 0) //attack
						this->attack += im[i].attB;
					if (im[i].defB != 0) //defence
						this->defense += im[i].defB;
					if (im[i].spdB != 0) //speed
						this->speed += im[i].spdB;
				}
			}
		}
	}
}

void entity::monitorHealth()
{
	if (this->currentHealth > this->maxHealth)
		this->currentHealth = this->maxHealth;
}

void entity::giveRandomStats(int difficultyLevel)
{
	if (difficultyLevel == 0)
	{
		this->maxHealth = 8+rand()%5;
		this->currentHealth = this->maxHealth;
		this->attack = 4+rand()%3;
		this->defense = 4+rand()%2;
		this->speed = 4 + rand()%2;
	}
	else if (difficultyLevel == 1)
	{
		this->maxHealth = 20+rand()%3;
		this->currentHealth = this->maxHealth;
		this->attack = 10+rand()%3;
		this->defense = 10+rand()%9;
		this->speed = 9+rand()%4;
	}
	else if (difficultyLevel == 2)
	{
		this->maxHealth = 60+rand()%11;
		this->currentHealth = this->maxHealth;
		this->attack = 15+rand()%4;
		this->defense = 15+rand()%9;
		this->speed = 16+rand()%5;
	}
	else if (difficultyLevel == 3)
	{
		this->maxHealth = 95+rand()%11;
		this->currentHealth = this->maxHealth;
		this->attack = 35+rand()%11;
		this->defense = 35+rand()%17;
		this->speed = 35+rand()%11;
	}
}

void entity::checkBattles(vector<entity>& enemyList)
{
	//check collision between enemy and player
	for (int i=0;i<enemyList.size();i++)
		if (enemyList[i].getXPos() == this->getXPos())
			if (enemyList[i].getYPos() == this->getYPos())
			{
				this->battle(enemyList[i]);
				this->checkIfNextLevel();
			}
}

void entity::saveData(int saveSlot,int mapNumber)
{
	//create the directory name
	char buffer[10];
	string directory = "Saves/slot";
	directory += itoa(saveSlot,buffer,10);
	directory += ".txt";

	//open the file for writing
	ofstream file(directory);
	file << this->name << endl;
	file << this->level << endl;
	file << this->currentHealth << endl;
	file << this->maxHealth << endl;
	file << this->attack << endl;
	file << this->defense << endl;
	file << this->speed << endl;
	file << this->xPos << endl;
	file << this->yPos << endl;
	file << this->experience << endl;
	file << mapNumber << endl;
	file.close();
}

int entity::loadData(int saveSlot)
{
	char buffer[30];
	string directory = "Saves/slot";
	directory += itoa(saveSlot,buffer,10);
	directory += ".txt";

	//open the file for reading
	string temp; //converting strings to numnbers
	ifstream file(directory);

	if (!file)
		throw FileMissingEx();

	if (file.eof())
		return -1;

	getline(file,this->name);

	if (file.eof())
		return -1;

	getline(file,temp);
	this->level = atoi(temp.c_str());
	getline(file,temp);
	this->currentHealth = atoi(temp.c_str());
	getline(file,temp);
	this->maxHealth = atoi(temp.c_str());
	getline(file,temp);
	this->attack = atoi(temp.c_str());
	getline(file,temp);
	this->defense = atoi(temp.c_str());
	getline(file,temp);
	this->speed = atoi(temp.c_str());
	getline(file,temp);
	this->xPos = atoi(temp.c_str());
	getline(file,temp);
	this->yPos = atoi(temp.c_str());
	getline(file,temp);
	this->experience = atoi(temp.c_str());
	getline(file,temp);
	int mapNumber = atoi(temp.c_str());

	return mapNumber;
}