/*
*	Programmer:		Patrick Yee
*	Date:			September 20, 2005
*/

#pragma once
#include "sprite.h"

/***************************************************************************************/
#define SAFE_DELETE(p)			{ if(p) {delete p; p = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{ if(p) {delete[] p; p = NULL;}}
#define SAFE_RELEASE(p)			{ if(p) {p->Release(); p = NULL;}}
/***************************************************************************************/

class Font :
	public Sprite
{
public:
	Font(void);
	~Font(void);

	// draw the sprite on the screen
	HRESULT Draw(char curPos, LPD3DXSPRITE m_SprMan);
	HRESULT WriteMessage(char msg[], LPD3DXSPRITE m_SprMan);
};
