#include "World.h"
#include "RenderMachine.h"

extern World gameWorld;
extern RenderMachine cRender;
extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;

//Programmer: Daniel R
//Revisions:
CPowerup::CPowerup()
{
	iPowerupType = kRockets;
	iMovementDirection = kMoveDown;
	cRender.SetUpSprite(sPowerupSprite, powerupSpriteBullet);
	PowerupON = false;
}

//Programmer: Daniel R
//Revisions:
void CPowerup::AlternatePowerupType()
{
	iPowerupType++;
	if(iPowerupType > kRockets)
	{
		iPowerupType = kBullets;
	}
}

//Programmer: Daniel R
//Revisions:
void CPowerup::UpdatePowerup()
{
	cRender.RenderImage(sPowerupSprite);
	if( (gameWorld.GetWorldGameClock()->GetCounter() % 120) == 0)
	{
		AlternatePowerupType();
		ChangePowerupFile();
	}
	//commented out for JC's testing
	if( (gameWorld.GetWorldGameClock()->GetCounter() % 40) == 0)
	{
		Move();
	}
}

//Programmer: Daniel R
//Revisions:
void CPowerup::Move()
{
	iMovementDirection = ((rand() % 7) + 3);	//random between 0 & 7 + 3 to reach the enumerated direction values
	switch(iMovementDirection)
	{
	case kMoveUp:
		sPowerupSprite.movey -= sPowerupSprite.height;
		sPowerupSprite.y += sPowerupSprite.movey;
		break;
	case kMoveDownP:	//Added to give a down movement a better chance to eventually to get to player
	case kMoveDownP1:
	case kMoveDownP2:
	case kMoveDown:
		sPowerupSprite.movey += sPowerupSprite.height;
		sPowerupSprite.y += sPowerupSprite.movey;
		break;
	case kMoveLeft:
		sPowerupSprite.movex -= sPowerupSprite.width;
		sPowerupSprite.x += sPowerupSprite.movex;
		break;
	case kMoveRight:
		sPowerupSprite.movex += sPowerupSprite.width;
		sPowerupSprite.x += sPowerupSprite.movex;
		break;
	}

	//If the powerup went too far to the left or right
	if( ( sPowerupSprite.x < 0 ) || ( sPowerupSprite.x + sPowerupSprite.width > SCREEN_WIDTH ) )
	{
		//move back
		sPowerupSprite.x -= sPowerupSprite.movex;
	}

	//If the powerup went too far up or down
	if( ( sPowerupSprite.y < 0 ) || ( sPowerupSprite.y + sPowerupSprite.height > SCREEN_HEIGHT ) )
	{
		//move back
		sPowerupSprite.y -= sPowerupSprite.movey;    
	}

	sPowerupSprite.movex = 0;
	sPowerupSprite.movey = 0;
}

void CPowerup::ChangePowerupFile()
{
	if(iPowerupType == kBullets)
	{
		sPowerupSprite.filePath = "Sprites\\PowerUp_Scatter.JPG";
	}
	if(iPowerupType == kLaser)
	{
		sPowerupSprite.filePath = "Sprites\\PowerUp_Laser.JPG";
	}
	if(iPowerupType == kRockets)
	{
		sPowerupSprite.filePath = "Sprites\\PowerUp_Rocket.JPG";
	}
	cRender.LoadImage(sPowerupSprite);
}

//added by Kai 9-20-06
SPRITE CPowerup::GetPowerupSprite()
{
	return sPowerupSprite;
}


//added by JC 9-20-06
int CPowerup::GetPowerupType()
{
	return iPowerupType;
}

//Programmer: Daniel R
//Revisions:
void CPowerup::TurnPowerupOn()
{
	PowerupON = true;
}

//Programmer: Daniel R
//Revisions:
void CPowerup::TurnPowerupOff()
{
	PowerupON = false;
}

//Programmer: Daniel R
//Revisions:
bool CPowerup::IsOn()
{
	if(PowerupON)
		return true;
	else
		return false;
}

//Programmer: Daniel R
//Revisions: JC
void CPowerup::CreatePowerup(SPRITE target)
{
	iPowerupType = rand() % 3;
	sPowerupSprite.x = target.x;
	sPowerupSprite.y = target.y;
	ChangePowerupFile();
}