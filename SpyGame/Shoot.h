#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "sprite.h"

/***************************************************************************************/
#define SAFE_DELETE(p)			{ if(p) {delete p; p = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{ if(p) {delete[] p; p = NULL;}}
#define SAFE_RELEASE(p)			{ if(p) {p->Release(); p = NULL;}}
/***************************************************************************************/

class Shoot :
	public Sprite
{
public:

	Shoot(void);
	~Shoot(void);
	bool Move();

	HRESULT Fire(int cur, LPD3DXSPRITE SprMan);
	void SetPos(int X, int Y);
	void DeleteBullet();
	//bool Collison(Sprite *CSprite);
};
