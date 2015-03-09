/*
*	Programmer:		Patrick Yee
*	Date:			September 13, 2005
*	Description:	The keyboard capturing
*/
#pragma once
#include <windows.h>
#include <stdlib.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

/***************************************************************************************/
#define SAFE_DELETE(p)			{ if(p) {delete p; p = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{ if(p) {delete[] p; p = NULL;}}
#define SAFE_RELEASE(p)			{ if(p) {p->Release(); p = NULL;}}
/***************************************************************************************/

class Keyboard
{
public:
	Keyboard(void);
	~Keyboard(void);

	// Initialize the keyboard
	HRESULT InitKeyboard(LPDIRECTINPUT8 DI, HWND hWnd);

	// If the key down.
	bool IsKeyDown(int Key);
	void Release();

private:
	LPDIRECTINPUTDEVICE8 m_pKeyDev;
	char m_keyBuffer[256];
	bool m_bInit;
};
