#include "Unit.h"
#include "RenderMachine.h"
#include "GameClock.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#ifndef LEVELDEF
#define LEVELDEF
class Level
{
private:
	SPRITE BackGround;
	FileArray *currentEnemy;
	int currentLevel;
	bool updated;
	bool changingLevel;

public:
	Level(){ currentEnemy = new FileArray; currentLevel = 1;}
	~Level(){ delete currentEnemy; }
	void initialize();
	void Update();
	void RenderLevel();
	void ChangeLevel();
	void LoadEnemies();
	void SetChangingLevel();
	int GetCurrentLevel();
};

#endif