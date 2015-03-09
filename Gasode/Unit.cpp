#include "Unit.h"

Unit::Unit()
{
}

Unit::~Unit()
{
}

void Unit::SetSpeed(float s)
{
}

float Unit::GetSpeed()
{
	return 0;
}

int Unit::GetState()
{
	return iState;
}

void Unit::Attack()
{
}

int Unit::GetHealth()
{
	return iHealth;
}

SPRITE Unit::GetSprite()
{
	return sUnit;
}
bool Unit::ChangeHealth(int weaponDamage)
{
	iHealth -= weaponDamage;
	if(iHealth <= 0)
		return true;
	else return false;
}