/*
*	Programmer:		Patrick Yee
*	Date:			September 13, 2005
*	Description:	Where are the devices are.
*/
#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include ".\keyboard.h"

/***************************************************************************************/
#define SAFE_DELETE(p)			{ if(p) {delete p; p = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{ if(p) {delete[] p; p = NULL;}}
#define SAFE_RELEASE(p)			{ if(p) {p->Release(); p = NULL;}}
/***************************************************************************************/

class Engine
{
public:
	Engine(void);
	~Engine(void);

	HRESULT GameInit(HINSTANCE, char appTitle[]);

	HRESULT InitD3Device();
	HRESULT PostRender();

	void ShowError(char FuncName[], char ErrMsg[]){
		char *out = new char[strlen(FuncName) + strlen(ErrMsg) + 50];

		strcpy(out, "\n--------------------------------------\n\n");
		strcat(out, FuncName);
		strcat(out, "\n\t\t");
		strcat(out, ErrMsg);
		strcat(out, "\n\n");
		OutputDebugString(out);
	}
protected:
	// window data.
	HWND m_hWnd;
	HBRUSH m_hBrush;
	int m_WndHeight;
	int m_WndWidth;
	bool m_bWindowed;

	// directX Objects
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3Dev;
	DWORD *m_pData;

	// direct input stuff
	LPDIRECTINPUT8  m_pDI;
	Keyboard m_KB;
};
