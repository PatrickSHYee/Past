#pragma once
#include "Unit.h"
#include "PoundDefs.h"
#include <string>

#ifdef WINDOWS
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <stdlib.h>
#include "dxgraphics.h"
#endif


enum{
	startScreenSDLSprite,
	startScreenSprite,
	playerSprite,
	playerDeathSprite,
	backgroundSprite,
	enemyDeathSprite,
	bossDeathSprite,
	bulletSpriteLv0,
	bulletSpriteLv1,
	bulletSpriteLv2,
	bulletSpriteLv3,
	laserSpriteLv1,
	laserSpriteLv2,
	laserSpriteLv3,
	rocketSpriteLv1,
	rocketSpriteLv2,
	rocketSpriteLv3,
	powerupSpriteBullet,
	powerupSpriteLaser,
	powerupSpriteRocket,
	CreditsScreenSprite,
	backgroundSprite2,
	enemyBulletSprite,
	enemy_Scooter,
	enemy_Dart,
	enemy_Pincer,
	enemy_Tank,
	enemy_Skiffy,
	enemy_Warbird,
	BombSprite,
	boss_Lvl1,
};

class RenderMachine
{
public:
	void Initialize();
	void LoadImage(SPRITE &sourceSprite);
	void RenderImage(SPRITE sourceSprite);
#ifdef SDL
	SDL_Surface* LoadImageSDL(char *filename);
	void RenderImageSDL(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
#endif

#ifdef WINDOWS
	LPDIRECT3DTEXTURE9 LoadImageDirectX(char *filename);
	void RenderImageDirectX(SPRITE sourceSprite);
#endif
	SPRITE SetUpSprite(SPRITE &sourceSprite, int Type);

	RenderMachine(void);
	~RenderMachine(void);
};
