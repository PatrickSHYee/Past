#include ".\keyboard.h"

Keyboard::Keyboard(void)
{
	ZeroMemory(&m_keyBuffer, sizeof(m_keyBuffer));
	m_pKeyDev = NULL;  // make sure we have a fresh device
	m_bInit = false;
}

Keyboard::~Keyboard(void)
{
}

void Keyboard::Release(){
	m_pKeyDev->Unacquire();
	SAFE_RELEASE(m_pKeyDev);
}
HRESULT Keyboard::InitKeyboard(LPDIRECTINPUT8 DI, HWND hWnd){
	if (FAILED(DI->CreateDevice(GUID_SysKeyboard, &m_pKeyDev, NULL))){
		return E_FAIL;
	}

	if (FAILED(m_pKeyDev->SetDataFormat(&c_dfDIKeyboard))){
		return E_FAIL;
	}

	if (FAILED(m_pKeyDev->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))){
		return E_FAIL;
	}

	if (FAILED(m_pKeyDev->Acquire())){
		return E_FAIL;
	}

	m_bInit = true;
	return S_OK;
}

bool Keyboard::IsKeyDown(int key){
	HRESULT res = m_pKeyDev->GetDeviceState(sizeof(m_keyBuffer), m_keyBuffer);

	if (!m_bInit){
		return false;
	}
	if (FAILED(res)){
		// if we lost the device
		if (res = DIERR_INPUTLOST){
			while (res == DIERR_INPUTLOST){
				res = m_pKeyDev->Acquire();
			}

			if (SUCCEEDED(res))
				m_pKeyDev->GetDeviceState(sizeof(m_keyBuffer), &m_keyBuffer);
			else
				return false;
		} else
			return false;
	}

	if (m_keyBuffer[key] & 0x80){
		return true;
	} else
		return false;
}