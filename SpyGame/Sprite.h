//Name:		Alfredo Orquiz
//File:		Sprite.h
//Date:		8-23-2005
//Desc:		This object is the sprite class which supports transparent background,
//			font and animated sprite objects
// History Revision -
//	- Added the Safe release

#include <d3dx9.h>
#include <d3d9.h>

#ifndef SPRITE_H
#define SPRITE_H

/***************************************************************************************/
#define SAFE_DELETE(p)			{ if(p) {delete p; p = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{ if(p) {delete[] p; p = NULL;}}
#define SAFE_RELEASE(p)			{ if(p) {p->Release(); p = NULL;}}
/***************************************************************************************/
class Sprite
{
public:
	Sprite();
	~Sprite();

	//tasks
	HRESULT Draw(int cur, LPD3DXSPRITE SprMan);
	HRESULT LoadTexture(LPDIRECT3DDEVICE9 pDev, char TextureFile[], int FrameCount, int NumCols,
							int NumRows);
	HRESULT LoadTexture(LPDIRECT3DDEVICE9 pDev, char BulletTexture[]);
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return m_Texture;
	}

	//helper functions
	//will access private parts
	int GetWidth();
	int GetHeight();
	int GetXPos();
	int GetYPos();
	int GetCurFrame();
	int GetFrameCount();
	void InCurFrame();
	void DeCurFrame();
	bool IsIncrementing();
	void SetIncrementing(bool val);
	void DrawSprite(LPD3DXSPRITE m_pSpriteManager);
	int GetColumn();
	void SetSpeed(int SpdX, int SpdY);
	void Move(int ScreenWidth, int ScreenHeight);
	void SetPos(int X, int Y);
	bool Collison(Sprite *CSprite);

	// for the enemy thing
	bool visible;
protected:
	int m_X, m_Y;
	int m_SpdX, m_SpdY;
	int m_Width, m_Height;
	int m_CurFrame, m_FrameCount, m_Rows, m_Columns;
	bool m_isIncrementing;
	LPDIRECT3DTEXTURE9 m_Texture;
	RECT m_srcRect;
};

#endif