#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include ".\font.h"

class PowerUp
{
public:
	PowerUp(void);
	PowerUp(LPD3DXSPRITE SprMan);
	~PowerUp(void);

	HRESULT ShowPwrUp(bool, LPD3DXSPRITE m_SprMan);
	int Collision(Sprite target);

private:
	Font m_PwdUp;
	D3DXIMAGE_INFO m_picInfo;
};
