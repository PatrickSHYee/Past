/*
*	Programmer:		Patrick Yee
*	Date:			September 13, 2005
*	Description:	Makes the game run.
*/
#include <Windows.h>
#include ".\game.h"
#include ".\engine.h"

// main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pstrCmdLine, int iCmdShow){
	Game g_Game;

	g_Game.GameInit(hInstance, "Our Game");
	g_Game.Run();
	return 0;
}