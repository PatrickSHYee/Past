#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"
#include "Weapon.h"
#include "listgeneric.h"
#include "SpecSound.h"

class Player : public Unit
{
protected:

	int iLives;
	int iScore;
	int iBombs;
	ListGeneric ProjectileList;
	int iWeaponType;
	int iWeaponLvl;
	int iWeaponTimer;

	int iRocketLvl;

	bool died;
	bool respawned;
	int respawnTime;
	bool keydown;

public:
	Player();
	~Player();
	void Init();
	void UpdatePlayer();
	bool Death();
	void Move();
	void RenderPlayer();
	int RenderLives();
	int RenderScore();
	int RenderBombs();
	int GetLives();
	int GetScore();
	int GetBombs();
	void AddScore(int score);

	void DecrementLives();	
	bool isAlive();
	bool isRespawned();
	int Bomb();

	void MakeProjectiles();

	void AddProjectile(CWeapon* Projectile);
	CWeapon *GetProjectile(int i);
	int GetNumberOfProjectiles();
	void RemoveProjectile(int i);

	void CollectedPowerup(int PowerupType);

};

#endif