#include "GameClock.h"

//Programmer: Daniel R
//Revisions:


enum{ kBullets, kLaser, kRockets, kMoveUp, kMoveDown, kMoveLeft, kMoveRight, kMoveDownP, kMoveDownP1, kMoveDownP2 };

class CPowerup
{
private:
	int iPowerupType;
	char* pPowerupSpriteType;
	SPRITE sPowerupSprite;
	int iMovementDirection;

	bool PowerupON;

public:
	CPowerup();
	//~CPowerup();
	void AlternatePowerupType();
	void UpdatePowerup();
	void Move();
	void ChangePowerupFile();
	SPRITE GetPowerupSprite();

	void TurnPowerupOn();					//Daniel R - added 9/22/06
	void TurnPowerupOff();					//Daniel R - added 9/22/06
	bool IsOn();							//Daniel R - added 9/22/06
	void CreatePowerup(SPRITE target);

	//added by JC 9-20-06
	int GetPowerupType();
};