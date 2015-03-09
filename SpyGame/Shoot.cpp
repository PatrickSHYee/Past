#include ".\shoot.h"

Shoot::Shoot(void)
{
	int m_BulletWidth = 0;
	int m_BulletHeight = 0;
	int m_BulletX = 0;
	int m_BulletY = 0;
} //end ctor

Shoot::~Shoot(void)
{
} //end dtor

//draws the bullet
HRESULT Shoot::Fire(int cur, LPD3DXSPRITE SprMan)
{
	// set position
	D3DXVECTOR3 position((float)m_X, (float)m_Y, 0.0f);

	int m_CurFrame = cur;

	// source rect
	RECT SrcRect;
	SrcRect.left = m_Width * (m_CurFrame % m_Columns);
	SrcRect.top = m_Height * (m_CurFrame / m_Columns);
	SrcRect.right = SrcRect.left + m_Width;
	SrcRect.bottom = SrcRect.top + m_Height;

	if (FAILED(SprMan->Draw(GetTexture(), &SrcRect, NULL, &position, D3DCOLOR_XRGB(255, 255, 255)))){
		return E_FAIL;
	}
	return S_OK;
} //end Draw

void Shoot::DeleteBullet(){
	SAFE_RELEASE(m_Texture);
}

//increments the position of the bullet
bool Shoot::Move()
{

	m_Y -= 10;

	if(m_Y <= 0)
		{
			SAFE_RELEASE(m_Texture);
			return true;
		}
	else
		return false;
}

//sets the start position of the bullet
void Shoot::SetPos(int X, int Y)
{
	m_X = X+15;
	m_Y = Y-50;
}