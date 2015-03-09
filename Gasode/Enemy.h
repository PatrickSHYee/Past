/*
Programmer:  Patrick Yee
Description: In the game, there is a creation of enemy.  The enemy has an update, which is
the brain.  See functions for additional 
*/
#ifndef ENEMY_H
#define ENEMY_H

#include "Unit.h"
#include "RenderMachine.h"
#include "listgeneric.h"
#include "Weapon.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#include <math.h>
//#include "vector2d.h"

#ifdef WINDOWS
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdio.h>
#include "dxgraphics.h"
#include "game.h"
#endif

#ifdef SDL
//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#endif

// type
enum
{
	Air,
	Ground
};

// iState
enum{
	boss,
	norm,
	miniBoss,
};

class Enemy:public Unit
{
private:
	SPRITE* target;
	int targetX, targetY;
	int projX, projY; 
	int past;
	int steps;
	int score;

	bool died;
	bool doneDying;

	ListGeneric eProjectileList;

	// boss thingy
	int xMove;
	int yMove;

public:
	Enemy(void);
	~Enemy();
	void Attack();

	void createBasic(int type);
	bool GetSpriteImage(int type);
	void UpdateEnemy();
	void Physics();
	bool EndOfScreen();
	void Render();

	void GetPlayer();
	void GetPlayerXY();
	void MoveToPosition();
	bool EnemyDeath();
	void SetEnemyDied(bool Died);
	bool IsDoneDying();
	bool IsDead();
	int getScore(){return score;}
	void UpdateEnemyWeapons();
	void DestoryEnemy();
	void BossUpdate();
	ListGeneric Boss_Firing;
	void changeState(int state){iState = state;}

	void AddProjectile(CWeapon* Projectile);
	CWeapon *GetProjectile(int i);
	int GetNumberOfProjectiles();
	void RemoveProjectile(int i);
};

#endif