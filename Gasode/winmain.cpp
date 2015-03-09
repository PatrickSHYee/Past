#include "PoundDefs.h"
#include "Unit.h"
#include "Player.h"
#include "Enemy.h"

bool GameLoop();
//void StartMenu();

int SCREEN_WIDTH = 480;
int SCREEN_HEIGHT = 640;

#ifdef WINDOWS
//Beginning Game Programming
//Chapter 7
//winmain.cpp - Windows framework source code file
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdio.h>
#include "dxgraphics.h"
#include "game.h"

HWND g_hWnd;
//window event callback function
LRESULT WINAPI WinProc( HWND g_hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_DESTROY:
		//release the Direct3D device
		if (d3ddev != NULL) 
			d3ddev->Release();

		//release the Direct3D object
		if (d3d != NULL)
			d3d->Release();

		//call the "front-end" shutdown function
		Game_End(g_hWnd);

		//tell Windows to kill this program
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc( g_hWnd, msg, wParam, lParam );
}


//helper function to set up the window properties
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	//create the window class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX); 

	// fill the struct with info
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WinProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = NULL;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = APPTITLE;
	wc.hIconSm       = NULL;

	//set up the window with the class info
	return RegisterClassEx(&wc);
}


//entry point for a Windows program
int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR     lpCmdLine,
				   int       nCmdShow)
{
	MSG msg;
	//HWND g_hWnd;

	//register the class
	MyRegisterClass(hInstance);

	// set up the screen in windowed or fullscreen mode?
	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPED;

	//create a new window
	g_hWnd = CreateWindow(
		APPTITLE,              //window class
		APPTITLE,              //title bar
		style,                 //window style
		CW_USEDEFAULT,         //x position of window
		CW_USEDEFAULT,         //y position of window
		SCREEN_WIDTH,          //width of the window
		SCREEN_HEIGHT,         //height of the window
		NULL,                  //parent window
		NULL,                  //menu
		hInstance,             //application instance
		NULL);                 //window parameters

	// was there an error creating the window?
	if (!g_hWnd)
		return FALSE;

	//display the window
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	if (!Init_Direct3D(g_hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN))
		return 0;

	//initialize the game
	if (!Game_Init(g_hWnd))
	{
		MessageBox(g_hWnd, "Error initializing the game", "Error", MB_OK);
		return 0;
	}

	//main message loop
	int done = 0;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			//look for quit message
			if (msg.message == WM_QUIT)
				done = 1;

			// decode and pass messages on to WndProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			//process game loop (else prevents running after window is closed)
			Game_Run(g_hWnd);
	}

	return (int)msg.wParam;
}
#endif

#ifdef SDL
////The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "SDL/SDL_ttf.h"

//The attributes of the screen
const int SCREEN_BPP = 32;

const int FRAMES_PER_SECOND = 20;

//The surfaces that will be used
SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;

SDL_Event event;

//The font that's going to be used
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 255, 255, 255 };

void RenderText(int x, int y, char *text)
{
	//Render the text

	message = TTF_RenderText_Solid( font, text, textColor );

	//If there was an error in rendering the text
	if( message == NULL )
	{

	}

	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface( message, 0, screen, &offset );
	//Apply the images to the screen
	// apply_surface( 0, 0, background, screen );  
	//apply_surface( 0, 200, message, screen );


}
int main( int argc, char* args[] )
{
	static bool quit = false;

	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		return 1;    
	}

	//Set up the screen
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	//If there was in error in setting up the screen
	if( screen == NULL )
	{
		return 1;    
	}    
	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		return false;    
	}

	//Open the font
	font = TTF_OpenFont( "lazy.ttf", 28 );

	//Set the window caption
	SDL_WM_SetCaption( "Gasode", NULL );

	while(!quit)
	{
		quit = GameLoop();

		while( SDL_PollEvent( &event ) )
		{   
			//If the user has Xed out the window
			if( event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
			{
				//Quit the program
				quit = true;
			}
		}
		if( SDL_Flip( screen ) == -1 )
		{
			return 1;    
		}
	} 

	//Free the surfaces
	// SDL_FreeSurface( message );
	// SDL_FreeSurface( background );

	//Close the font that was used
	//TTF_CloseFont( font );

	//Quit SDL_ttf
	// TTF_Quit();


	//Quit SDL
	SDL_Quit();

	return 0;    
}

#endif
