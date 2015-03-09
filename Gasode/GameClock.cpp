#include ".\gameclock.h"
#include "World.h"
extern World gameWorld;

GameClock::GameClock(void)
{
	numFrames = 0;
	fps = 0;
	startTime = 0;
	/*static */counter = 0;
	seconds = 0;
	for(int i=0; i<10; i++)
		lastTimeCheck[i] = GetGameTickCount();

}
bool GameClock::Frame()
{
	int tempTime = GetGameTickCount();

	if ( tempTime - startTime >= (1000/60))
	{
		startTime = tempTime;
		EnemyCheck();
		fps = numFrames;
		numFrames = 0;
		counter++;
		return false;
	}
	numFrames++;

	if(counter > 300 )
		counter = 0;

	return true;

}
double GameClock::GetFPS()
{
	return fps;
}

void GameClock::InitGameClock()
{
	startTime = GetGameTickCount();
}

int GameClock::GetCounter()
{
	return counter;
}

int GameClock::GetGameTickCount()
{
#ifdef WINDOWS
	return timeGetTime();
#endif
#ifdef SDL
	return SDL_GetTicks();
#endif
}
int GameClock::GetSeconds()
{
	return (GetGameTickCount()/1000);
}

bool GameClock::CheckTime(int timeCheck, int type)
{
	if(GetGameTickCount() >= lastTimeCheck[type] + timeCheck)
	{
		lastTimeCheck[type] = GetGameTickCount();
		return true;
	}
	else return false;
}
void GameClock::NewLevel(FileArray *currEn)
{
	currentEnemy = currEn;
	lastTimeCheck[currentEnemyTime] = currentEnemy->timeSpawn;
	lastTimeCheck[levelStart] = GetGameTickCount();
}
void GameClock::EnemyCheck()
{
	if(startTime - lastTimeCheck[levelStart] > lastTimeCheck[currentEnemyTime] && currentEnemy->next != NULL)
	{
		FileArray *tempFA = currentEnemy;
		gameWorld.CreateNewEnemy(currentEnemy->enemyType);
		currentEnemy = currentEnemy->next;
		lastTimeCheck[currentEnemyTime] = currentEnemy->timeSpawn;
		delete tempFA;
	}
	if(currentEnemy->next == NULL && gameWorld.enemiesOnSrc <= 0)
		gameWorld.GetLevel()->SetChangingLevel();
}