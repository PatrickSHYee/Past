/*
*	Programmer:		Patrick Yee
*	Date:			September 13, 2005
*	Description:	Where the player, the enemies, backgrounds, and the controls are loaded and done.
*/

#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "engine.h"
#include ".\keyboard.h"
#include "sprite.h"
#include "Background.h"
#include ".\shoot.h"

#ifndef GAME_H
#define GAME_H

/***************************************************************************************/
#define SAFE_DELETE(p)			{ if(p) {delete p; p = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{ if(p) {delete[] p; p = NULL;}}
#define SAFE_RELEASE(p)			{ if(p) {p->Release(); p = NULL;}}
/***************************************************************************************/

class Game :
	public Engine
{
public:
	Game(void);
	~Game(void);

	HRESULT Run();
	HRESULT Render();
	HRESULT Background();
	HRESULT LoadSprImg();
	HRESULT PostRender();

	// player & enemy functions
	HRESULT ShowPlayer(int pos);
	HRESULT ShowEnemy();
	HRESULT CollisionChecking();

	// Controls functions
	HRESULT Controls();
	bool Timer();
	HRESULT Pause();

	// Screen displays
	HRESULT TitleScreen();

private:
	// player info.
	int m_plyrHeight, m_plyrWidth, m_plyrX, m_plyrY, m_plyrScore, m_plyrPos;
	int m_lives, m_pwdLvl;
	long m_plyrSpdX, m_plyrSpdY, m_BGSpd;
	bool CanFire;
	int curE;

	// game stuff
	int m_TimerMin, m_TimerSec, m_TimerMillisec;

	// Sprite management data
	LPD3DXSPRITE m_pSprMan;
	Sprite m_PlayerSpr, m_PauseScr, m_ControlScr, m_EndingScreen, m_TitleScreen, m_EnemySpr[3];
	CBackground m_Background;
	Shoot m_Bullet;

	// directX Objects
	LPDIRECT3DSURFACE9 m_pBackSurf;
};
extern Game *g_Game;
#endif
