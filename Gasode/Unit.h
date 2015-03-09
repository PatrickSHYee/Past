#ifndef UNIT_H
#define UNIT_H

#include "PoundDefs.h"
#include <string>
#ifdef SDL
#include "SDL/SDL.h"
#endif

#ifdef WINDOWS
#include <d3d9.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "dxgraphics.h"
#endif

struct Border
{
	int top;
	int left;
	int bottom;
	int right;
};

struct SPRITE{
	SPRITE() { filePath = new char[]; }
	~SPRITE() { /*delete []filePath;*/ }

	int x,y;
	int width,height;
	int movex,movey;
	Border BoundingBox;
	char* filePath;
	int curframe,lastframe;
	int animdelay,animcount;

#ifdef SDL
	SDL_Surface *unitSprite;
#endif
#ifdef WINDOWS
	LPDIRECT3DTEXTURE9 unitSprite;
	//LPDIRECT3DSURFACE9 unitSprite;
#endif
};

class Unit
{
protected:
	float fSpeed;
	int iState;
	int iHealth;
	SPRITE sUnit;

public:
	Unit();
	~Unit();
	float GetSpeed();
	void SetSpeed(float);
	int GetState();
	int GetHealth();
	bool ChangeHealth(int weaponDamage);
	void Attack();
	SPRITE GetSprite();
};

#endif