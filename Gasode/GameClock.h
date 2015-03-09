#pragma once
#include "PoundDefs.h"
#include "time.h"

#define RocketDelay 1000
#define BaseWeaponDelay 160
#define BulletDelay 160
#define LaserLv1Delay 120
#define LaserLv3Delay 80
#define BombDelay 1000

struct FileArray
{
	int timeSpawn;
	int enemyType;
	FileArray *next;
	FileArray(){ next = NULL; }
	~FileArray(){ /*delete next;*/ }
};

enum{weaponFire, rocketFire, bombFire, levelStart, currentEnemyTime, enemyFire};

class GameClock
{
private:
	float numFrames;
	int startTime;
	float fps;
	int counter;
	float seconds;
	int lastTimeCheck[10];
	FileArray *currentEnemy;

public:
	GameClock(void);
	bool Frame();
	double GetFPS();
	void InitGameClock();
	int GetCounter();
	int GetGameTickCount();
	int GetSeconds();
	bool CheckTime(int timeCheck, int type);
	void NewLevel(FileArray *currEn);
	void EnemyCheck();

};
