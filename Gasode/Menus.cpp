#include "Unit.h"
#include "Player.h"
#include "Enemy.h"
#include "World.h"
#include "RenderMachine.h"

extern World gameWorld;
extern RenderMachine cRender;


bool StartMenu()
{
#ifdef SDL
	Uint8 *keystates = SDL_GetKeyState( NULL );

	static SPRITE startScreen = cRender.SetUpSprite(startScreen, startScreenSDLSprite);
	if(keystates[SDLK_RETURN])
	{
		gameWorld.GetLevel()->LoadEnemies();
		return true;
	}
#endif
#ifdef WINDOWS
	static SPRITE startScreen = cRender.SetUpSprite(startScreen, startScreenSprite);

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		gameWorld.GetLevel()->LoadEnemies();
		return true;
	}
#endif

	cRender.RenderImage(startScreen);

	return false;
}
bool QuitGame()
{
	static SPRITE CreditsScreen = cRender.SetUpSprite(CreditsScreen, CreditsScreenSprite);
#ifdef SDL
	Uint8 *keystates = SDL_GetKeyState( NULL );

	if(keystates[SDLK_RETURN])
		return true;
#endif

#ifdef WINDOWS

	if (KEY_DOWN(VK_RETURN)){
		return true;}	
#endif
	cRender.RenderImage(CreditsScreen);

	return false;
}