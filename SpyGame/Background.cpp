// *****************************************************************************
// Author:		Robert O'Neil
// File:		Font.h
// Date:		8/23/2005
// Description: This object is the backgound class which supports scrolling a
//				background regardless of the texture dimensions.
//
// Revision History

#include "Background.h"

// *****************************************************************************
// ctor
CBackground::CBackground( )
{
	m_Offset = 0;
}// end ctor

// *****************************************************************************
// dtor
CBackground::~CBackground( )
{
	SAFE_RELEASE(m_Texture);
}// end dtor

// *****************************************************************************
// Draw function
HRESULT CBackground::Draw( LPD3DXSPRITE SpriteManager, int hWndWidth, int hWndHeight )
{
	RECT rct;
    rct.left=0;
	rct.right=hWndWidth;

	D3DXVECTOR3 pos(0,0,0);

	// Draw our sprites
	
	// Top sprite		
	rct.top=m_Height-m_Offset;
	rct.bottom=m_Height;
		
	SpriteManager->Draw( m_Texture, &rct, NULL,&pos,0xFFFFFFFF );

	// Bottom sprite
	rct.top=0;
	rct.bottom=m_Height-m_Offset;

	pos.y=(float)m_Offset;

	SpriteManager->Draw( m_Texture, &rct, NULL,&pos,0xFFFFFFFF );

	// Done
	m_Offset -= m_ScrollSpeed;
	if( m_Offset > m_Height )
		m_Offset = 0;
	return S_OK;
	
}// end Draw

// *****************************************************************************
// Load background
HRESULT CBackground::LoadBackground( HWND hWnd, LPDIRECT3DDEVICE9 pDev,
									char TextureFile[ ] )
{
	D3DXIMAGE_INFO picInfo;

	// get the image info
	if( FAILED( D3DXGetImageInfoFromFile( TextureFile, &picInfo ) ) )
	{
		return E_FAIL;
	}

	// setup our sprite variables
	m_Width = picInfo.Width;
	m_Height = picInfo.Height;



	// create the texture
	if( FAILED( D3DXCreateTextureFromFileEx( pDev, TextureFile,
		m_Width, m_Height, 1, D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_XRGB( 255, 0, 255 ), &picInfo, NULL, &m_Texture ) ) )
	{
		return E_FAIL;
	}
	return S_OK;
}// end load background

// *****************************************************************************
// Set scroll speed of background
void CBackground::SetScrollSpeed( int Speed )
{
	m_ScrollSpeed = Speed;
}// end set scroll speed