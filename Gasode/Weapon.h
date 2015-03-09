#include "PoundDefs.h"

#ifndef WEAPONS_H
#define WEAPONS_H

#include "Unit.h"
#include "RenderMachine.h"

class CWeapon
{
private:
	SPRITE sProjectile;
	bool bFireing;

	int wepType;
	int wepDamage;

public:
	CWeapon();
	CWeapon(int);
	~CWeapon();
	bool UpdateWeapon();
	void Fire();
	void RenderWeapon();
	void SetPosition(int offset_x,int offset_y);
	void SetPositionForEnemy(int Enemy_x,int Enemy_y);
	void ModPosition(int offset_x,int offset_y);
	void SetX(int x);
	void SetY(int y);
	int GetWeaponDamage();
	SPRITE GetProjectileSprite();
};

#endif
