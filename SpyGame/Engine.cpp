/*
*	Programmer:		Patrick Yee
*	Date:			September 13, 2005
*	Description:	Where are the devices are.
*/

#include ".\engine.h"

//----------------------WndProc will handle the windows messages.-------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMge, WPARAM wParam, LPARAM lParam){
	switch(uMge)
	{
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
		default:
			{
				return DefWindowProc(hWnd, uMge, wParam, lParam);
			}
	}
}
//------------------------------------------------------------------------

Engine::Engine(void)
{
	// init memory and pointers
	m_pD3D = NULL;
	m_pD3Dev = NULL;

	m_bWindowed = true;  // if false then fullscreen.

	// if m_bWindowed = true then window resolution as follows.
	m_WndWidth = 800;
	m_WndHeight = 600;
}

Engine::~Engine(void)
{
	// deleting brush objects
	DeleteObject(m_hBrush);

	// releasing the pointers for the D3D devices.
	SAFE_RELEASE(m_pD3Dev);
	SAFE_RELEASE(m_pD3D);
	SAFE_RELEASE(m_pDI);
	m_KB.Release();
}

// Init function will create the window for the game.
HRESULT Engine::GameInit(HINSTANCE hInstance, char appTitle[]){
	// make brush for background.
	LOGBRUSH lBrush;
	lBrush.lbColor = RGB(192, 192, 192);  // color: black
	lBrush.lbStyle = BS_SOLID;
	lBrush.lbHatch = NULL;
	m_hBrush = CreateBrushIndirect(&lBrush);

	if (m_hBrush == NULL){
		ShowError("Engine::GameInit", "Failure to create background brush");
		return E_FAIL;
	}

	// setup window class;
	WNDCLASSEX WC;
	WC.cbSize = sizeof(WNDCLASSEX);
	WC.style = CS_HREDRAW | CS_VREDRAW;
	WC.cbClsExtra = 0;
	WC.cbWndExtra = 0;
	WC.lpfnWndProc = WndProc;
	WC.hInstance = hInstance;
	WC.hbrBackground = m_hBrush;
	WC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WC.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WC.hCursor = LoadCursor(NULL, IDC_CROSS);
	WC.lpszMenuName = NULL;
	WC.lpszClassName = appTitle;

	// register and create window.
	RegisterClassEx(&WC);
	m_hWnd = CreateWindowEx(NULL, appTitle, appTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_WndWidth, m_WndHeight, NULL, NULL, hInstance, NULL);
	if (m_hWnd == NULL){
		ShowError("Engine::GameInit", "Failure to create game window!");
		return E_FAIL;
	}

	// init the direct input devices
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL))){
		ShowError("Engine::GameInit", "Failure to create the direct input device!");
		return E_FAIL;
	}
	
	return S_OK;
}

// Get the Direct3D device ready
HRESULT Engine::InitD3Device(){
	D3DPRESENT_PARAMETERS d3dpp;  // presentation parameters
	D3DDISPLAYMODE d3dmm;  // display mode.

	if (m_pD3Dev)
		SAFE_RELEASE(m_pD3Dev);

	// create device
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL){
		ShowError("Application::InitD3Device", "Could not create the Direct3D COM Interface");
		return E_FAIL;
	}

	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3dmm))){
		ShowError("Application::InitD3Device", "Could not get adapater display mode.");
		return E_FAIL;
	}

	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferHeight = m_WndHeight;
	d3dpp.BackBufferWidth = m_WndWidth;
	d3dpp.BackBufferFormat = d3dmm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = m_bWindowed;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// create the device
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3Dev))){
		ShowError("Application::InitD3Device", "Could not create the render device!");
		return E_FAIL;
	}

	return S_OK;
}