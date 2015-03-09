// *****************************************************************************
// Author:		Robert O'Neil
// File:		Font.h
// Date:		8/23/2005
// Description: This object is the backgound class which supports scrolling a
//				background regardless of the texture dimensions.
//
// Revision History
//	- Redefined SAFE_RELEASE

#include "Sprite.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H

// Background class header file
class CBackground
{
public:
	// ctor
	CBackground( );
	// dtor
	~CBackground( );

	// tasks
	HRESULT Draw( LPD3DXSPRITE SpriteManager, int hWndWidth, int hWndHeight );
	HRESULT LoadBackground( HWND hWnd, LPDIRECT3DDEVICE9 pDev, char TextureFile[ ] );
	void SetScrollSpeed( int Speed );

private:
	int m_Top, m_Bottom, m_Left, m_Right;
	int m_ScrollSpeed;
	int m_Offset;
	int m_Width, m_Height;
	LPDIRECT3DTEXTURE9 m_Texture;
};

#endif