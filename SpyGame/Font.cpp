#include ".\font.h"

Font::Font(void)
{
	m_Texture = NULL;
}

Font::~Font(void)
{
	SAFE_RELEASE(m_Texture);
}

HRESULT Font::Draw(char cur, LPD3DXSPRITE SprMan){
	// set position
	D3DXVECTOR2 position((float)m_X, (float)m_Y);

	m_CurFrame = cur - 32;

	// source rect
	m_srcRect.left = m_Width * (m_CurFrame % m_Columns);
	m_srcRect.top = m_Height * (m_CurFrame / m_Columns);
	m_srcRect.right = m_srcRect.left + m_Width;
	m_srcRect.bottom = m_srcRect.top + m_Height;

	if (FAILED(SprMan->Draw(GetTexture(), &m_srcRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255)))){
		return E_FAIL;
	}
	return S_OK;
}

HRESULT Font::WriteMessage(char msg[], LPD3DXSPRITE SprMan){
	unsigned int len = strlen(msg);
	for (unsigned int i = 0; i < len; i++){
		SetPos(m_X + m_Width, m_Y);

		if (FAILED(Draw(msg[i], SprMan))){
			SprMan->End();
			return E_FAIL;
		}
	}
	return S_OK;
}