#include "Weapon.h"
#include "World.h"

extern RenderMachine cRender;
extern World gameWorld;
extern int SCREEN_WIDTH;

#define MAX_WEP_DMG 3

CWeapon::CWeapon()
{
	cRender.SetUpSprite(sProjectile, bulletSpriteLv0);
	wepType = bulletSpriteLv0;
	bFireing = false;
	wepDamage = 1;
}

CWeapon::CWeapon(int WeaponType)
{
	cRender.SetUpSprite(sProjectile, WeaponType);
	wepType = WeaponType;
	bFireing = false;
	switch(WeaponType)
	{
	case bulletSpriteLv0:
	case bulletSpriteLv1:
	case bulletSpriteLv2:
	case bulletSpriteLv3:
		wepDamage = 1;
		break;
	case laserSpriteLv1:
	case laserSpriteLv2:
		wepDamage = 2;
		break;
	case laserSpriteLv3:
		wepDamage = 3;
		break;
	case rocketSpriteLv1:
		wepDamage = 2;
		break;
	}

}

CWeapon::~CWeapon()
{
}

bool CWeapon::UpdateWeapon()
{
	if(bFireing)
	{
		sProjectile.y += sProjectile.movey;
		sProjectile.x += sProjectile.movex;
		RenderWeapon();

		if(sProjectile.y > 1 && sProjectile.x > 1 && sProjectile.x < SCREEN_WIDTH && sProjectile.y < SCREEN_HEIGHT)
			return true;
	}

	return false;

}

void CWeapon::Fire()
{
	bFireing = true;

	switch(wepType)
	{
	case bulletSpriteLv0:
		cRender.SetUpSprite(sProjectile, bulletSpriteLv0);
		SetPosition(26,10);
		break;
	case bulletSpriteLv1:
		cRender.SetUpSprite(sProjectile, bulletSpriteLv1);
		SetPosition(26,10);
		break;
	case bulletSpriteLv2:
		cRender.SetUpSprite(sProjectile, bulletSpriteLv1);
		SetPosition(26,10);
		break;
	case bulletSpriteLv3:
		cRender.SetUpSprite(sProjectile, bulletSpriteLv1);
		SetPosition(26,10);
		break;
	case laserSpriteLv1:
		cRender.SetUpSprite(sProjectile, laserSpriteLv1);
		SetPosition(26,10);
		break;
	case laserSpriteLv2:
		cRender.SetUpSprite(sProjectile, laserSpriteLv2);
		SetPosition(26,10);
		break;
	case laserSpriteLv3:
		cRender.SetUpSprite(sProjectile, laserSpriteLv3);
		SetPosition(22,10);
		break;
	case rocketSpriteLv1:
		cRender.SetUpSprite(sProjectile, rocketSpriteLv1);
		SetPosition(24,10);
		break;
	case rocketSpriteLv2:
		cRender.SetUpSprite(sProjectile, rocketSpriteLv1);
		SetPosition(24,10);
		break;
	case rocketSpriteLv3:
		cRender.SetUpSprite(sProjectile, rocketSpriteLv1);
		SetPosition(24,10);
		break;
	case enemyBulletSprite:
		cRender.SetUpSprite(sProjectile, enemyBulletSprite);
		break;
	}
}

void CWeapon::RenderWeapon()
{
	cRender.RenderImage(sProjectile);
}

void CWeapon::SetPosition(int offset_x, int offset_y)
{
	SPRITE sTemp = gameWorld.GetPlayerSprite();
	sProjectile.x = sTemp.x + offset_x; //offset Bullet  width and
	sProjectile.y = sTemp.y - offset_y; //height from Player sprite to center it in front of player
}

void CWeapon::SetPositionForEnemy(int Enemy_x, int Enemy_y)
{
	sProjectile.x = Enemy_x; //offset Bullet  width and
	sProjectile.y = Enemy_y; //height from Player sprite to center it in front of player
}

void CWeapon::ModPosition(int offset_x, int offset_y)
{
	sProjectile.x += offset_x;
	sProjectile.y += offset_y;
}

SPRITE CWeapon::GetProjectileSprite()
{
	return sProjectile;
}
int CWeapon::GetWeaponDamage()
{
	return wepDamage;
}

void CWeapon::SetX(int x)
{
	sProjectile.movex = x *2;
}

void CWeapon::SetY(int y)
{
	sProjectile.movey = y *2;
}