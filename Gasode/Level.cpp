#include "level.h"
#include "World.h"
extern RenderMachine cRender;
extern World gameWorld;
//extern sourceSprite;
extern int SCREEN_HEIGHT;


void Level::initialize()
{
	changingLevel = false;
	updated = false;
	cRender.SetUpSprite(BackGround,backgroundSprite);
}
void Level::Update()
{
	//scrolls the background
	BackGround.y += BackGround.movey;
	if (BackGround.y > BackGround.height - SCREEN_HEIGHT)
		BackGround.y = 0;

	//render the image
	cRender.RenderImage(BackGround);
	if(changingLevel)
		ChangeLevel();
}
void Level::RenderLevel()
{
	cRender.RenderImage(BackGround);
}
void Level::ChangeLevel()
{
	if (BackGround.movey <= 150 && updated == true)
	{
		//scrolls the background
		BackGround.movey --;

		if(BackGround.movey < 3)
		{
			BackGround.movey = 3;
			updated = false;
			changingLevel = false;
		}
	}
	else
	{
		//this code is for the speeding up to change the level
		//once movey is 150 - level changes
		BackGround.movey++;
	}
	if (BackGround.movey >= 150)
	{
		//once level is loaded background is set back
		//to the default 
		char temp[30];
		currentLevel++;
		sprintf(temp, "Sprites\\Level%dBackground.png", currentLevel);
		BackGround.filePath = temp;
		cRender.LoadImage(BackGround);
		LoadEnemies();
		updated = true;
		BackGround.movey = 150;
	}

	//LoadEnemies();
}

void Level::LoadEnemies()
{
	//loads the enemies and the spawn times into seperate arrays
	//from a text file

	ifstream inFile;
	int enemyData;
	char temp[50];
	FileArray *fileLocation = currentEnemy;

	sprintf(temp, "Levels\\SpawnTimes%d.txt",currentLevel);
	inFile.open(temp);
	//inFile.open("Levels\\SpawnTimes1.txt");

	if (!inFile)		//if the infile does not exist
	{
		return;	
	}
	inFile >> enemyData;
	while(enemyData != -999)
	{
		fileLocation->timeSpawn = enemyData;
		inFile >> enemyData;
		fileLocation->enemyType = enemyData;
		inFile >> enemyData;
		if(fileLocation->timeSpawn != -999)
		{
			fileLocation->next = new FileArray;
			fileLocation = fileLocation->next;
		}
	}
	inFile.close();
	gameWorld.GetWorldGameClock()->NewLevel(currentEnemy);
}
void Level::SetChangingLevel()
{
	changingLevel = true;
}
int Level::GetCurrentLevel()
{
	return currentLevel;
}