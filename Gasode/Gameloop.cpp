//Both SDL and Windows come to this Gameloop after initiating and creating a Window.
//This is where the game state is initialized, and functions are called to perform
// actions based on where the game is.

#include "Unit.h"
#include "Player.h"
#include "Enemy.h"
#include "World.h"
#include "RenderMachine.h"
#include "PoundDefs.h"

#ifdef SDL
World gameWorld;
#endif
extern World gameWorld;
RenderMachine cRender;


bool StartMenu();
bool QuitGame();

enum {
	gameStateInitialize,
	gameStateStart,
	gameStatePlay,
	gameStatePause,
	gameCreditState,
	gameStateQuit,
};

int gameState = gameStateInitialize;

bool GameLoop()
{
	switch(gameState)
	{
	case gameStateInitialize:
		cRender.Initialize();
		gameWorld.InitializeWorld();
		gameState= gameStateStart;
		break;
	case gameStateStart:
		if(StartMenu())
			gameState = gameStatePlay;
		break;
	case gameStatePlay:
		if(gameWorld.Update())
			gameState = gameCreditState;
		break;
	case gameStatePause:
		break;
	case gameCreditState:
		if(	QuitGame())
			gameState = gameStateQuit;
		break;
	case gameStateQuit:
		return true;
		break;
	}
	return false;
}

