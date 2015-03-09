#include ".\rendermachine.h"

#ifdef SDL
extern SDL_Surface *screen;	//Destination
#endif

#ifdef WINDOWS
extern LPD3DXSPRITE sprite_handler;
#endif

extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;


RenderMachine::RenderMachine(void)
{
}

RenderMachine::~RenderMachine(void)
{
}
void RenderMachine::Initialize()
{
#ifdef WINDOWS
	//D3DXCreateSprite(d3ddev, &sprite_handler);
#endif
}

void RenderMachine::LoadImage(SPRITE &sourceSprite)
{
#ifdef SDL
	sourceSprite.unitSprite = LoadImageSDL(sourceSprite.filePath);
#endif
#ifdef WINDOWS
	sourceSprite.unitSprite = LoadImageDirectX(sourceSprite.filePath);
#endif
}

void RenderMachine::RenderImage(SPRITE sourceSprite)
{
#ifdef SDL
	if(sourceSprite.height > SCREEN_HEIGHT)
		RenderImageSDL(sourceSprite.x,sourceSprite.y-sourceSprite.height+SCREEN_HEIGHT,sourceSprite.unitSprite,screen,0);
	else
		RenderImageSDL(sourceSprite.x,sourceSprite.y,sourceSprite.unitSprite,screen,0);
#endif
#ifdef WINDOWS
	RenderImageDirectX(sourceSprite);
#endif
}

#ifdef SDL
SDL_Surface* RenderMachine::LoadImageSDL(char *filename)
{
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load( filename );

	//If nothing went wrong in loading the image
	if( loadedImage != NULL )
	{
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );

		//Free the old image
		SDL_FreeSurface( loadedImage );

		if( optimizedImage != NULL )
		{
			//Color key surface
			SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0xFF, 0xFF, 0xFF ) );
		}
	}

	//Return the optimized image
	return optimizedImage;
}

void RenderMachine::RenderImageSDL(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface( source, clip, screen, &offset );
}
#endif

#ifdef WINDOWS
//ADD DIRECTX RENDERING BELOW
LPDIRECT3DTEXTURE9 RenderMachine::LoadImageDirectX(char *filename)
{
	//return LoadSurface(filename, D3DCOLOR_ARGB(0,255,255,255) );
	return LoadTexture(filename, D3DCOLOR_ARGB(0,255,255,255) );

}
void RenderMachine::RenderImageDirectX(SPRITE sourceSprite)
{
	RECT* rect;

	rect = new RECT;


	//Used if the bitmap is off the screen (y). Mainly used for Background
	if(sourceSprite.height > SCREEN_HEIGHT)  //sourceSprite.y < 0 || sourceSprite.y + 
	{
		rect->bottom = sourceSprite.height - sourceSprite.y;
		rect->top =  rect->bottom - SCREEN_HEIGHT;
		rect->left = 0;
		rect->right = SCREEN_WIDTH;
		//d3ddev->StretchRect(sourceSprite.unitSprite, rect, backbuffer, NULL ,D3DTEXF_NONE);
		sprite_handler->Draw(
			sourceSprite.unitSprite, 
			rect, // the return value of the toRect function of SPRITE
			NULL,
			&D3DXVECTOR3(0,0,0),
			D3DCOLOR_XRGB(255,255,255));



	}	
	else	//Used for all bitmaps that are completely on the screen
	{
		rect->left = 0;
		rect->top = 0;
		rect->right = sourceSprite.width;
		rect->bottom = sourceSprite.height;
		sprite_handler->Draw(
			sourceSprite.unitSprite, 
			rect, // the return value of the toRect function of SPRITE
			NULL,
			&D3DXVECTOR3(sourceSprite.x,sourceSprite.y,0),
			D3DCOLOR_XRGB(255,255,255));
		//d3ddev->StretchRect(sourceSprite.unitSprite, NULL, backbuffer, rect ,D3DTEXF_NONE);
	}

	delete rect;
}
#endif

SPRITE RenderMachine::SetUpSprite(SPRITE &sourceSprite, int Type)
{
	switch(Type)
	{
	case startScreenSDLSprite:
		sourceSprite.x = 0;
		sourceSprite.y = 0;
		sourceSprite.movex = 0;
		sourceSprite.movey = 0;
		sourceSprite.width = 480;
		sourceSprite.height = 640;
		sourceSprite.filePath = "Sprites\\StartScreenSDL.png";
		break;
	case startScreenSprite:
		sourceSprite.x = 0;
		sourceSprite.y = 0;
		sourceSprite.movex = 0;
		sourceSprite.movey = 0;
		sourceSprite.width = 480;
		sourceSprite.height = 640;
		sourceSprite.filePath = "Sprites\\StartScreen.png";
		break;
	case playerSprite:
		sourceSprite.x = 210;
		sourceSprite.y = 500;
		sourceSprite.movex = 0;
		sourceSprite.movey = 0;
		sourceSprite.width = 64;
		sourceSprite.height = 44;
		sourceSprite.filePath = "Sprites\\MainPlayer.png";
		break;
	case playerDeathSprite:
		sourceSprite.movex = 0;
		sourceSprite.movey = 0;
		sourceSprite.animcount = 13;
		sourceSprite.animdelay = 5;
		sourceSprite.curframe = 1;
		sourceSprite.lastframe = 0;
		sourceSprite.width = 96;
		sourceSprite.height = 116;
		sourceSprite.filePath = "Sprites\\PlayerDeath\\PlayerDeathSprite1.png";
		break;
	case backgroundSprite:
		sourceSprite.x = 0;
		sourceSprite.y = 0;
		sourceSprite.movex = 0;
		sourceSprite.movey = 3;
		sourceSprite.width = 480;
		sourceSprite.height = 2048;
		sourceSprite.filePath = "Sprites\\Level1Background.png"; 
		break;
	case enemyDeathSprite:
		sourceSprite.movex = 0;
		sourceSprite.movey = 0;
		sourceSprite.animcount = 5;
		sourceSprite.animdelay = 15;
		sourceSprite.curframe = 1;
		sourceSprite.lastframe = 0;
		sourceSprite.width = 72;
		sourceSprite.height = 56;
		sourceSprite.filePath = "Sprites\\EnemyDeath\\EnemyDeathSprite1.png";
		break;
	case bossDeathSprite:
		sourceSprite.movex = 0;
		sourceSprite.movey = 0;
		sourceSprite.animcount = 5;
		sourceSprite.animdelay = 15;
		sourceSprite.curframe = 1;
		sourceSprite.lastframe = 0;
		sourceSprite.width = 342;
		sourceSprite.height = 207;
		sourceSprite.filePath = "Sprites\\EnemyDeath\\BossDeathSprite1.png";
		break;
	case bulletSpriteLv0:
	case bulletSpriteLv1:
	case bulletSpriteLv2:
	case bulletSpriteLv3:
		sourceSprite.x = 0;
		sourceSprite.y = 0;
		sourceSprite.movex = 0;
		sourceSprite.movey = -10;
		sourceSprite.width = 10;
		sourceSprite.height = 10;
		sourceSprite.filePath = "Sprites\\Shot.png";
		break;
	case enemyBulletSprite:
		sourceSprite.x = 0;
		sourceSprite.y = 0;
		sourceSprite.movex = 0;
		sourceSprite.movey = -10;
		sourceSprite.width = 10;
		sourceSprite.height = 10;
		sourceSprite.filePath = "Sprites\\Shot.png";
		break;
	case laserSpriteLv1:
		sourceSprite.x = 0;
		sourceSprite.y = 0;
		sourceSprite.width = 8;
		sourceSprite.height = 40;
		sourceSprite.movex = 0;
		sourceSprite.movey = -10;
		sourceSprite.filePath = "Sprites\\Laser.png";
		break;
	case laserSpriteLv2:
		sourceSprite.x = 0;
		sourceSprite.y = 0;
		sourceSprite.width = 8;
		sourceSprite.height = 40;
		sourceSprite.movex = 0;
		sourceSprite.movey = -10;
		sourceSprite.filePath = "Sprites\\Laser.png";
		break;
	case laserSpriteLv3:
		sourceSprite.x = 0;
		sourceSprite.y = 0;
		sourceSprite.width = 18;
		sourceSprite.height = 40;
		sourceSprite.movex = 0;
		sourceSprite.movey = -10;
		sourceSprite.filePath = "Sprites\\LaserLv3.png";
		break;
	case rocketSpriteLv1:
		sourceSprite.x = 0;
		sourceSprite.y = 0;
		sourceSprite.movex = 0;
		sourceSprite.movey = -6;
		sourceSprite.width = 12;
		sourceSprite.height = 22;
		sourceSprite.filePath = "Sprites\\Rocket.png";
		break;
	case rocketSpriteLv2:
		sourceSprite.x = 0;
		sourceSprite.y = 0;
		sourceSprite.movex = 0;
		sourceSprite.movey = -6;
		sourceSprite.width = 12;
		sourceSprite.height = 22;
		sourceSprite.filePath = "Sprites\\Rocket.png";
		break;
	case rocketSpriteLv3:
		sourceSprite.x = 0;
		sourceSprite.y = 0;
		sourceSprite.movex = 0;
		sourceSprite.movey = -6;
		sourceSprite.width = 12;
		sourceSprite.height = 22;
		sourceSprite.filePath = "Sprites\\Rocket.png";
		break;
	case powerupSpriteBullet:
		sourceSprite.x = 50;
		sourceSprite.y = 50;
		sourceSprite.width = 19;
		sourceSprite.height = 20;
		sourceSprite.filePath = "Sprites\\PowerUp_Scatter.JPG";
		break;
	case powerupSpriteLaser:
		sourceSprite.width = 19;
		sourceSprite.height = 20;
		sourceSprite.filePath = "Sprites\\PowerUp_Laser.JPG";
		break;
	case powerupSpriteRocket:
		sourceSprite.width = 19;
		sourceSprite.height = 20;
		sourceSprite.filePath = "Sprites\\PowerUp_Rocket.JPG";
		break;
	case CreditsScreenSprite:
		sourceSprite.x = 0;
		sourceSprite.y = 0;
		sourceSprite.movex = 0;
		sourceSprite.movey = 0;
		sourceSprite.width = 480;
		sourceSprite.height = 640;
		sourceSprite.filePath = "Sprites\\creditScreen.png";
		break;
	case backgroundSprite2:
		sourceSprite.x = 0;
		sourceSprite.y = 0;
		sourceSprite.movex = 0;
		sourceSprite.movey = 3;
		sourceSprite.width = 480;
		sourceSprite.height = 2048;
		sourceSprite.filePath = "Sprites\\Level2Background.png"; 
		break;
	case enemy_Scooter:
		sourceSprite.width = 42;
		sourceSprite.height = 32;
		sourceSprite.filePath = "Sprites\\EnemySprites\\Scooter.png";
		break;
	case enemy_Dart:
		sourceSprite.width = 26;
		sourceSprite.height = 38;
		sourceSprite.filePath = "Sprites\\EnemySprites\\Dart.png";
		break;
	case enemy_Pincer:
		sourceSprite.width = 24;
		sourceSprite.height = 24;
		sourceSprite.filePath = "Sprites\\EnemySprites\\Pincer.png";
		break;
	case enemy_Tank:
		sourceSprite.width = 43;
		sourceSprite.height = 35;
		sourceSprite.filePath = "Sprites\\EnemySprites\\Tank.png";
		break;
	case enemy_Skiffy:
		sourceSprite.width = 94;
		sourceSprite.height = 110;
		sourceSprite.filePath = "Sprites\\EnemySprites\\Skiffy.png";
		break;
	case enemy_Warbird:
		sourceSprite.width = 104;
		sourceSprite.height = 48;
		sourceSprite.filePath = "Sprites\\EnemySprites\\Warbird.png";
		break;
	case BombSprite:
		sourceSprite.x = 0;
		sourceSprite.y = 0;
		sourceSprite.movex = 0;
		sourceSprite.movey = 0;
		sourceSprite.width = 480;
		sourceSprite.height = 640;
		sourceSprite.filePath = "Sprites\\Bomb.png";
		break;
	case boss_Lvl1:
		sourceSprite.width = 341;
		sourceSprite.height = 207;
		sourceSprite.filePath = "Sprites\\EnemySprites\\level1.png";
		break;
	}

	LoadImage(sourceSprite);
	return sourceSprite;
}