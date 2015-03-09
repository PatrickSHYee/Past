// Beginning Game Programming
// Chapter 7
// Anim_Sprite program source code file


#include "PoundDefs.h"



#include "game.h"
#include "World.h"
#include "RenderMachine.h"

extern RenderMachine cRender;
extern D3DCOLOR fontColor;
extern LPD3DXFONT m_font;
bool GameLoop();


#ifdef WINDOWS
LPD3DXSPRITE sprite_handler;

World gameWorld;

#endif

// Handling fonts
LPD3DXFONT m_font;

// Create a colour for the text - in this case blue
D3DCOLOR fontColor = D3DCOLOR_ARGB(255,255,0,0);  

//initializes the game
int Game_Init(HWND hwnd)
{

#ifdef WINDOWS

	D3DXCreateSprite(d3ddev, &sprite_handler);

#endif


	// Create a D3DX font object
	D3DXCreateFont( d3ddev, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_font );

	//return okay
	return 1;
}

//the main game loop
void Game_Run(HWND hwnd)
{
#ifdef WINDOWS
	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;

	//start rendering
	if (d3ddev->BeginScene())
	{
		//d3ddev->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0,0,0));

		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);


		if(GameLoop())
			PostMessage(hwnd, WM_DESTROY, 0, 0);



		sprite_handler->End();



		//stop rendering
		d3ddev->EndScene();


		//update lives print to screen get iLives red working
		//m_Player->GetLives();


	}

	//display the back buffer on the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);

	//check for escape key (to exit program)
	if (KEY_DOWN(VK_ESCAPE))

	{
		PostMessage(hwnd, WM_DESTROY, 0, 0);
	}

#endif

}

//frees memory and cleans up before the game ends
void Game_End(HWND hwnd)
{

}


