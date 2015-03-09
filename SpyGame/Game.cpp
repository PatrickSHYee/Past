#include ".\game.h"

Game *g_Game = NULL;

Game::Game(void)
{
	m_pBackSurf = 0;

	// set to 3:00:0000
	m_TimerMin = 3;
	m_TimerSec = 0;
	m_TimerMillisec = 0;

	// Player info.
	m_plyrHeight = 100;
	m_plyrWidth = 80;
	m_plyrX = 399;
	m_plyrY = 500;
	m_plyrSpdX = 0;
	m_plyrSpdY = 0;
	m_BGSpd = 0;
	m_plyrScore = 0;
	m_plyrPos = 2;
	m_lives = 3;
	curE = 0;

	// Sprite stuff
	m_pSprMan = NULL;
}

Game::~Game(void)
{
	SAFE_RELEASE(m_pBackSurf);
	SAFE_RELEASE(m_pSprMan);
}

// clean up after stuff been rendered.
HRESULT Game::PostRender(){
	// end scenes
	if (!FAILED(m_pD3Dev->BeginScene()))
	{
		// begin the scene
		m_pSprMan->Begin(D3DXSPRITE_ALPHABLEND);
		// draw the pause screen
		m_EndingScreen.Draw(0, m_pSprMan);
		//m_GameOverScreen.Draw(0, m_pSprMan);

		m_pSprMan->End();
		m_pD3Dev->EndScene();
		// present
		m_pD3Dev->Present(NULL, NULL, NULL, NULL);

		Sleep(2500);
		
		return S_OK;
	}
	return E_FAIL;
}

HRESULT Game::Run(){

	// display window.
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	// Direct3D window initialization
	if (FAILED(InitD3Device())){
		ShowError("Application::Run", "The Direct3D device could not be initialized!");
		return 0;
	}

	// initialization sprite manager
	if (FAILED(D3DXCreateSprite(m_pD3Dev, &m_pSprMan))){
		ShowError("Engine::Run", "Failure to initialize sprite manager");
		return E_FAIL;
	}

	// initialize the keyboard
	if (FAILED(m_KB.InitKeyboard(m_pDI, m_hWnd))){
		ShowError("Engine::Run", "Failure to get the keyboard device");
		return E_FAIL;
	}

	// game loop
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));	
	if (FAILED(LoadSprImg()))
	{
		ShowError("Game::Run", "Failure to create surfaces.");
		return E_FAIL;
	}

	if (FAILED(TitleScreen())){
		ShowError("Game::Run", "Didn't load title screen");
		return E_FAIL;
	}
	while(!Timer()){
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			if (FAILED(Pause()))
			{
				m_TimerMillisec--;
				// Game loop goes here.
				//bullet movement
				CanFire=m_Bullet.Move();
				Controls();

				if (FAILED(CollisionChecking())){
					break;
				}
				Render();
			} else {break;}
		}

	}	
	PostRender();

	return S_OK;
}

// render stuff
HRESULT Game::Render(){
	m_pD3Dev->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(192, 192, 192), 1.0f, 0);  // clear screen.

	// lock 'em up
	D3DLOCKED_RECT lockRect;
	if (FAILED(m_pBackSurf->LockRect(&lockRect, NULL, 0))){
		ShowError("Engine::Render", "Failure to lock the back buffer surface.");
		return E_FAIL;
	}

	// get the buffer data area.
	m_pData = (DWORD*) (lockRect.pBits);

	// render the "needs" to draw directly to buffer
	for(int i=0; i < 100000; i++){
		m_pData[(((lockRect.Pitch/4) * (rand()%m_WndHeight)) + rand()%m_WndWidth)]= D3DCOLOR_XRGB(rand() %256, rand() %256, rand() %256);
	}

	m_pBackSurf->UnlockRect(); // unlock back buffer.

	// move the sprite then it will draw

	// render the sprite objects
	if (!FAILED(m_pD3Dev->BeginScene())){
		// move the sprite then it will draw
		m_pSprMan->Begin(D3DXSPRITE_ALPHABLEND);

		// the scrolling background
		if (FAILED(Background())){
			ShowError("Game::Render", "Failure to display the background");
			return E_FAIL;
		}

		// Show the player.
		if (FAILED(ShowPlayer(m_plyrPos))){
			ShowError("Game::Render", "Failure to show player");
			return E_FAIL;
		}

		// Show the Enemy
		/*if (FAILED(ShowEnemy())){
			ShowError("Game::Render", "Failure to show the enemy");
			return E_FAIL;
		}*/
		m_Bullet.Fire(0,m_pSprMan);
		m_pSprMan->End();
		m_pD3Dev->EndScene();
	}
	
	// place stuff on screen
	m_pD3Dev->Present(NULL, NULL, NULL, NULL);

	return S_OK;
}

bool Game::Timer(){
	if (m_TimerMillisec <= 0){
		if (m_TimerSec == 0){
			if (m_TimerMin == 0){
				return true;
			} else {
				m_TimerMin--;
				m_TimerSec = 60;
				m_TimerMillisec = 100;
			}
		} else {
			m_TimerSec--;
			m_TimerMillisec = 100;
		}
	} else {
		m_TimerMillisec--;
	}
	return false;
}

//**********************************************************************************
HRESULT Game::LoadSprImg(){
	// get a pointer to back buffer.
	if (FAILED(m_pD3Dev->GetBackBuffer(0,0, D3DBACKBUFFER_TYPE_MONO, &m_pBackSurf))){
		ShowError("Application::Render", "Could not GET the back buffer surface.");
		return E_FAIL;
	}

	// Background
	m_Background.LoadBackground(m_hWnd, m_pD3Dev, "pictures/background.bmp");

	// Load player sprite, load the position, and set the speed for the player
	if (FAILED(m_PlayerSpr.LoadTexture(m_pD3Dev, "pictures/car.bmp", 5, 5, 1))){
		ShowError("Game::LoadSprImg", "Failure to create player sprite");
		return E_FAIL;
	}
	m_PlayerSpr.SetPos(400, (500 - m_PlayerSpr.GetHeight()));
	m_PlayerSpr.SetSpeed(m_plyrSpdX, m_plyrSpdY);

	//load the bullet
	m_Bullet.SetPos(-10,-10);
	if(FAILED(m_Bullet.LoadTexture(m_pD3Dev, "pictures/bullet.bmp")))
	{
		return E_FAIL;
	}

	// Pause
	if (FAILED(m_PauseScr.LoadTexture(m_pD3Dev, "pictures/pause.bmp", 0, 1, 1))){
		ShowError("Game::LoadSprImg", "Failure to load Pause screen");
		return E_FAIL;
	}
	m_PauseScr.SetPos(0, 0);

	// Controls
	if (FAILED(m_ControlScr.LoadTexture(m_pD3Dev, "pictures/controls.bmp", 0, 1, 1))){
		ShowError("Game::LoadSprImg", "Failure to control screen.");
		return E_FAIL;
	}
	m_ControlScr.SetPos(0, 0);

	// ending screen
	if (FAILED(m_EndingScreen.LoadTexture(m_pD3Dev, "pictures/ending.bmp", 0, 1, 1))){
		ShowError("Game::LoadSprImg", "Failure to ending screen.");
		return E_FAIL;
	}
	m_EndingScreen.SetPos(0, 0);

	// title screen
	if (FAILED(m_TitleScreen.LoadTexture(m_pD3Dev, "pictures/title.bmp", 0, 1, 1))){
		ShowError("Game::LoadSprImg", "Failure to title screen bmp");
		return E_FAIL;
	}
	m_TitleScreen.SetPos(0, 0);

	// enemy
	for(curE = 0; curE < 3; curE++){
		if (FAILED(m_EnemySpr[curE].LoadTexture(m_pD3Dev, "pictures/enemy.bmp", 0, 1, 1))){
			ShowError("Game::LoadSprImg", "Failure to load enemy sprite picture");
			return E_FAIL;
		}
	}

	return S_OK;
}

// Displays the scrolling background
HRESULT Game::Background(){
	m_Background.SetScrollSpeed(m_BGSpd);
	m_Background.Draw(m_pSprMan, m_WndWidth, m_WndHeight);
	// score
	return S_OK;
}

//*****************************************
//  Player stuff (Code below)
HRESULT Game::ShowPlayer(int pos){
	
	m_PlayerSpr.SetSpeed(m_plyrSpdX, m_plyrSpdY);
	try{
		// screen collision: one-third of the screen.  When the player head towards of the screen.
		if (m_PlayerSpr.GetYPos() < m_WndHeight / 3){
			m_PlayerSpr.SetPos(m_PlayerSpr.GetXPos(), m_WndHeight / 3);
			m_plyrPos = 2;
		}
		
		// screen collision: three-fourth of the screen.  When the player backs on the bottom of screen.
		if (m_PlayerSpr.GetYPos() > (m_WndHeight / 4) * 3){
			m_PlayerSpr.SetPos(m_PlayerSpr.GetXPos(), (m_WndHeight / 4) * 3);
		}

		// screen collision: left of the road.
		if (m_PlayerSpr.GetXPos() < 160){
			m_plyrSpdX = 0;
			m_plyrPos = 0;
			m_PlayerSpr.SetPos(160, m_PlayerSpr.GetYPos());
		}

		// screen collision: right of the road
		if (m_PlayerSpr.GetXPos() > m_WndWidth - m_PlayerSpr.GetWidth() - 160){
			m_plyrSpdX = 0;
			m_plyrPos = 0;
			m_PlayerSpr.SetPos(m_WndWidth - m_PlayerSpr.GetWidth() - 160, m_PlayerSpr.GetYPos());
		}

		// if the car is stopped is doesn't move
		if (m_plyrSpdY == 0 && m_BGSpd == 0){
			m_PlayerSpr.SetPos(m_PlayerSpr.GetXPos(), m_PlayerSpr.GetYPos());
			m_plyrSpdX = 0;
		} else {
			m_PlayerSpr.Move(m_WndWidth, m_WndHeight);
		}

		// Screen Collision
		if (m_PlayerSpr.GetYPos() > 450){
			m_plyrPos = 2;
			m_plyrSpdX = 0;
		}
		if (m_plyrSpdY > 0){
			m_plyrPos = 4;
		}

		m_PlayerSpr.Draw(pos, m_pSprMan);
	} catch (...){
		ShowError("Game::ShowPlayer", "Failure to draw the player sprite");
		m_pSprMan->End();
		m_pD3Dev->EndScene();
		return E_FAIL;
	}
	return S_OK;
}
//  EnemyCar (Code below)
HRESULT Game::ShowEnemy(){
	for (curE = 0; curE < 3; curE++){
		if (m_EnemySpr[curE].visible){
			if (m_EnemySpr[curE].GetYPos() + m_EnemySpr[curE].GetHeight() > m_WndHeight){
				m_EnemySpr[curE].visible = false;
			}
			m_EnemySpr[curE].Move(m_WndWidth, m_WndHeight);
			m_EnemySpr[curE].Draw(0, m_pSprMan);
		} else {
			m_EnemySpr[curE].visible = true;
			m_EnemySpr[curE].SetPos((rand()  % 400) + 160, 0);
			m_EnemySpr[curE].SetSpeed(0, 3);
		}
	}
	return S_OK;
}
//  Controls - 
HRESULT Game::Controls(){
	// move player forward and background foward
	if (m_KB.IsKeyDown(DIK_UP) || m_KB.IsKeyDown(DIK_W)){
		m_BGSpd -= 1;
		if (m_BGSpd < -2)
			m_BGSpd = -2;
		m_plyrSpdY = m_BGSpd/2;
		m_plyrScore += -1 * m_BGSpd * 100;
		m_plyrPos = 2;
		m_plyrSpdX = 0;
	}

	// slow down the player and the background.
	if (m_KB.IsKeyDown(DIK_DOWN) || m_KB.IsKeyDown(DIK_S)){
		m_BGSpd += 1;
		m_plyrSpdY = m_BGSpd;
		if (m_BGSpd > 0){
			m_plyrSpdY += 2;
			m_BGSpd = 0;
		}
		if (m_plyrSpdY > 10)
			m_plyrSpdY = 0;

		m_plyrPos = 2;
		m_plyrSpdX = 0;
	}

	// move left for the player
	if (m_KB.IsKeyDown(DIK_LEFT) || m_KB.IsKeyDown(DIK_A)){
		Sleep(20);
		m_plyrPos = 0;
		m_plyrSpdX -= 1;
	}
	
	// move right for the player
	if (m_KB.IsKeyDown(DIK_RIGHT) || m_KB.IsKeyDown(DIK_D)){
		Sleep(20);
		m_plyrPos = 4;
		m_plyrSpdX +=1;
	}

	// right control key fires
	if ((m_KB.IsKeyDown(DIK_RCONTROL) || m_KB.IsKeyDown(DIK_SPACE)) && CanFire==true){
		m_Bullet.LoadTexture(m_pD3Dev, "pictures/bullet.bmp");
		m_Bullet.SetPos(m_PlayerSpr.GetXPos(), m_PlayerSpr.GetYPos());
		if(FAILED(m_Bullet.Fire(1, m_pSprMan)))
		{
			ShowError("Game::LoadSprImg", 
				"Failure to create bullet");
			return E_FAIL;
		}

	}
	return S_OK;
}

HRESULT Game::Pause(){
	if (m_KB.IsKeyDown(DIK_ESCAPE)){
		// display the pause screen.
		while (true){
			if (!FAILED(m_pD3Dev->BeginScene())){
				m_pSprMan->Begin(D3DXSPRITE_ALPHABLEND);
				m_PauseScr.Draw(0, m_pSprMan);
				m_pSprMan->End();
				m_pD3Dev->EndScene();
				m_pD3Dev->Present(NULL, NULL, NULL, NULL);
				Sleep(150);
				if (m_KB.IsKeyDown(DIK_1)){
					// display the whatever is option 1 is.
					while (true){
						if (!FAILED(m_pD3Dev->BeginScene())){
							m_pSprMan->Begin(D3DXSPRITE_ALPHABLEND);
							m_ControlScr.Draw(0, m_pSprMan);
							m_pSprMan->End();
							m_pD3Dev->EndScene();
							m_pD3Dev->Present(NULL, NULL, NULL, NULL);
						}
						if (m_KB.IsKeyDown(DIK_RETURN)){
								// display the pause again.
								break;
							}
					}
				}

				// returns to the game.
				if (m_KB.IsKeyDown(DIK_2)){
					m_pD3Dev->Clear(0,0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(192, 192, 192), 0.0f, 0);
					m_pSprMan->End();
					m_pD3Dev->EndScene();
					m_pD3Dev->Present(NULL, NULL, NULL, NULL);
					break;
				}

				// quits the game
				if (m_KB.IsKeyDown(DIK_ESCAPE)){
					PostQuitMessage(0);
					return S_OK;
				}
				
			}
		}
	}	
	return E_FAIL;
}

//// Title Screen
HRESULT Game::TitleScreen()
{
	while(!m_KB.IsKeyDown(DIK_RETURN)){
	// begin the scene
		if (!FAILED(m_pD3Dev->BeginScene()))
		{
			// begin the scene
			m_pSprMan->Begin(D3DXSPRITE_ALPHABLEND);
			// draw the game over screen
			m_TitleScreen.Draw(0, m_pSprMan);
			Sleep(100);

			// if the player presses ESCAPE, load the title screen
			// I don't know how you want to do this, but this will take you back to the
			// Title screen
			if (m_KB.IsKeyDown(DIK_RETURN))
			{
				// start the game
			}

			// end scenes
			m_pSprMan->End();
			m_pD3Dev->EndScene();
			// present
			m_pD3Dev->Present(NULL, NULL, NULL, NULL);
		}
	}
	return S_OK;
}// end Title Screen

HRESULT Game::CollisionChecking(){
	for (curE = 0; curE < 3; curE++){
		if (m_PlayerSpr.Collison(&m_EnemySpr[curE]) && m_lives != 0){
			m_lives--;
			m_PlayerSpr.SetPos(400, (500 - m_PlayerSpr.GetHeight()));
			m_EnemySpr[curE].SetSpeed(0, 0);
			m_EnemySpr[curE].visible = false;
		}

		if (m_Bullet.Collison(&m_EnemySpr[curE])){
			m_Bullet.DeleteBullet();
			m_EnemySpr[curE].visible = false;
		}
		if (m_lives == 0){
			return E_FAIL;
		}
	}
	return S_OK;
}