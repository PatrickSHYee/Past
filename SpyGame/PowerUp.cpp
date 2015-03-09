#include ".\powerup.h"

PowerUp::PowerUp(void)
{
}

PowerUp::PowerUp(LPD3DXSPRITE SprMan)
{
	D3DXGetImageInfoFromFile("picture/RollOvers.bmp", &m_picInfo);	
}

PowerUp::~PowerUp(void)
{
}

int PowerUp::Collision(Sprite target){
	return 0;
}

HRESULT PowerUp::ShowPwrUp(bool show, LPD3DXSPRITE SprMan){
	return S_OK;
}