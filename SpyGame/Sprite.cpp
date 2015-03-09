//Name:		Alfredo Orquiz
//File:		Sprite.cpp
//Date:		8-23-2005
//Desc:		object is sprite class which supports transparent background,
//			font and animated sprite objects

#include "sprite.h"

//ctor
Sprite::Sprite()
{
	m_X = 0;
	m_Y = 0;
	m_CurFrame = 0;
	m_isIncrementing = true;
	visible = false;
} //end ctor

//dtor
Sprite::~Sprite()
{
	SAFE_RELEASE(m_Texture);
} //end dtor

//draw the sprite on the screen
HRESULT Sprite::Draw(int cur, LPD3DXSPRITE SprMan)
{
	// set position
	D3DXVECTOR3 position((float)m_X, (float)m_Y, 0.0f);

	m_CurFrame = cur;

	// source rect
	m_srcRect.left = m_Width * (m_CurFrame % m_Columns);
	m_srcRect.top = m_Height * (m_CurFrame / m_Columns);
	m_srcRect.right = m_srcRect.left + m_Width;
	m_srcRect.bottom = m_srcRect.top + m_Height;

	if (FAILED(SprMan->Draw(GetTexture(), &m_srcRect, NULL, &position, D3DCOLOR_XRGB(255, 255, 255)))){
		return E_FAIL;
	}
	return S_OK;
	return S_OK;
} //end Draw

//sprite properties
void Sprite::DrawSprite(LPD3DXSPRITE m_pSpriteManager)
{
	D3DXVECTOR3 position((float) m_X, (float) m_Y, 0.0f);
	

	//create the source rect
	RECT srcRect;
	srcRect.left = m_Width * (m_CurFrame % m_Columns);
	srcRect.top = m_Height * (m_CurFrame / m_Columns);
	srcRect.right = srcRect.left + m_Width;
	srcRect.bottom = srcRect.top + m_Height;

	m_pSpriteManager->Draw(m_Texture, &srcRect, NULL, &position, D3DCOLOR_XRGB(255,255,255));

	//change the frame count
	//increase the frame count
	if(m_isIncrementing)
		InCurFrame();
	else
		DeCurFrame();
	
	//decide if we need to switch "directions"
	if(GetCurFrame() >= GetFrameCount())
			SetIncrementing(false);
	else if(GetCurFrame() <= 0)
			SetIncrementing(true);

	Sleep(20);

}

HRESULT Sprite::LoadTexture(LPDIRECT3DDEVICE9 pDev, char BulletTexture[]){
	D3DXIMAGE_INFO Bullet;
	
	//get bullet info
	if(FAILED(D3DXGetImageInfoFromFile(BulletTexture, &Bullet)))
	{
		return E_FAIL;
	}
	m_Width = Bullet.Width;
	m_Height = Bullet.Height;

	if(FAILED(D3DXCreateTextureFromFileEx(pDev, BulletTexture, Bullet.Width, Bullet.Height,
		1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255), &Bullet, NULL, &m_Texture)))
	{
		return E_FAIL;
	}
	return S_OK;
}
//load the sprite texture
HRESULT Sprite::LoadTexture(LPDIRECT3DDEVICE9 pDev, char TextureFile[], int FrameCount, int NumCols,
							int NumRows)
{
	D3DXIMAGE_INFO picInfo;

	//get image info
	if(FAILED(D3DXGetImageInfoFromFile(TextureFile, &picInfo)))
	{
		return E_FAIL;
	}

//fix me later
//----------------------------------------------------------------------------------------
	m_FrameCount = FrameCount;
	m_Columns = NumCols;
	m_Rows = NumRows;
//----------------------------------------------------------------------------------------

	//setup the sprite variables
	m_Width = picInfo.Width / m_Columns;
	m_Height = picInfo.Height / m_Rows;

	//create texture
	if(FAILED(D3DXCreateTextureFromFileEx(pDev, TextureFile, picInfo.Width, picInfo.Height,
		1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255), &picInfo, NULL, &m_Texture)))
	{
		return E_FAIL;
	}
	return S_OK;
} //end LoadTexture

//return the width of the sprite
int Sprite::GetWidth()
{
	return m_Width;
}
//return the height of the sprite
int Sprite::GetHeight()
{
	return m_Height;
}
//return the x position of the sprite
int Sprite::GetXPos()
{
	return m_X;
}
//return the y position of the sprite
int Sprite::GetYPos()
{
	return m_Y;
}
//return the current frame of the sprite
int Sprite::GetCurFrame()
{
	return m_CurFrame;
}
//return the count on the frame of the sprite
int Sprite::GetFrameCount()
{
	return m_FrameCount;
}
//return the frame count of the sprite
void Sprite::InCurFrame()
{
	m_CurFrame++;
}
//decrement rings
void Sprite::DeCurFrame()
{
	m_CurFrame--;
}
//increments the sprite frame
bool Sprite::IsIncrementing()
{
	return m_isIncrementing;
}
//set increments of the sprite frame
void Sprite::SetIncrementing(bool val)
{
	m_isIncrementing = val;
}
//checks the column of the sprite
int Sprite::GetColumn()
{
	return m_Columns;
}
//set the sprite speed flag
void Sprite::SetSpeed(int SpdX, int SpdY)
{
	m_SpdX = SpdX;
	m_SpdY = SpdY;
}
//move th sprite
void Sprite::Move(int ScreenWidth, int ScreenHeight)
{
	m_X += m_SpdX;
	m_Y += m_SpdY;
	
}
void Sprite::SetPos(int X, int Y)
{
	m_X = X;
	m_Y = Y;
}

bool Sprite::Collison(Sprite *CSprite){
	RECT thisRect, colRect, dest;

	// this sprite
	thisRect.left = m_X;
	thisRect.right = m_X + m_Width;
	thisRect.top = m_Y;
	thisRect.bottom = m_Y + m_Height;

	// collide sprite
	colRect.left = CSprite->m_X;
	colRect.right = CSprite->m_X + CSprite->m_Width;
	colRect.top = CSprite->m_Y;
	colRect.bottom = CSprite->m_Y + CSprite->m_Height;

	// change the sprite info for both sprite
	if (IntersectRect(&dest, &thisRect, &colRect)){
		m_SpdX -= m_SpdX;
		m_SpdY -= m_SpdY;
		m_X += m_SpdX;
		m_Y += m_SpdY;

		CSprite->m_SpdX -= CSprite->m_SpdX;
		CSprite->m_SpdY -= CSprite->m_SpdY;
		CSprite->m_X += CSprite->m_SpdX;
		CSprite->m_Y += CSprite->m_SpdY;
		return true;
	}
	return false;
}