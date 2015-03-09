#pragma once

#include "Player.h"
#include "Enemy.h"
#include "GameClock.h"
#include "Level.h"
#include "Powerup.h"


/*
Added by JC
* VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
* 0x40 : unassigned
* VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
*/
#define VK_A		0x41
#define VK_B		0x42
#define VK_C		0x43
#define VK_D		0x44
#define VK_E		0x45
#define VK_F		0x46
#define VK_G		0x47
#define VK_H		0x48
#define VK_I		0x49
#define VK_J		0x4A
#define VK_K		0x4B
#define VK_L		0x4C
#define VK_M		0x4D
#define VK_N		0x5E
#define VK_O		0x4F
#define VK_P		0x50
#define VK_Q		0x51
#define VK_R		0x52
#define VK_S		0x53
#define VK_T		0x54
#define VK_U		0x55
#define VK_V		0x56
#define VK_X		0x58
#define VK_W		0x57
#define VK_Y		0x59
#define VK_Z		0x5A
//end

#define MAX_POWERUP_NUM 3
#define MAX_LEVELS 2


class World
{
private:

	Player			*mPlayer;
	Level			*mLevel;
	GameClock		*mGameClock;
	int				numEnemies;

	ListGeneric		mPowerup;
	int				randomEnemy;
	//end Red

	//testing for JC - 9/25/06
	//CPowerup		*staticPowerup;
	//double		temp;


public:
	void InitializeWorld();
	bool Update();
	bool IsCollided(SPRITE spriteCheck1, SPRITE spriteCheck2);
	void CollisionDetection();
	void EnemyUpdate();
	World(void);
	~World(void);
	SPRITE GetPlayerSprite();
	SPRITE GetEnemySprite(int n);
	GameClock* GetWorldGameClock();
	void Bombs();
	void CreateNewEnemy(int type);
	Level* GetLevel();

	// public variables
	ListGeneric		mEnemies;
	int				enemiesOnSrc;
	SpecSound		sound;
};
