#include "Player.h"
#include "RenderMachine.h"
#include "World.h"

enum{
	laser = 0,
	exploding,
	bomb,
	rocketExploding,
	bullets,
};


extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;



#ifdef SDL
extern SDL_Event event;
extern SDL_Surface *load_image( std::string filename );
extern void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
void RenderText(int x, int y, char *text);
#endif

#ifdef WINDOWS
extern D3DCOLOR fontColor;
extern LPD3DXFONT m_font;
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
extern LPD3DXSPRITE sprite_handler;
#endif
extern RenderMachine cRender;
extern World gameWorld;

Player::Player()
{

}

Player::~Player()
{
	ProjectileList.Clear();
}

void Player::Init()
{
	respawned = false;
	died = false;
	keydown = false;
	iLives = 15;
	iScore = 0;
	iBombs = 10;

	respawnTime = 0;

	cRender.SetUpSprite(sUnit, playerSprite);

	iWeaponType = bulletSpriteLv0;
	iWeaponTimer = 8;
	iWeaponLvl = 0;
	iWeaponTimer = BaseWeaponDelay;
	iRocketLvl = 0;
}
int Player::RenderLives()
{	
	char temp[20];
	int lives = GetLives();
	sprintf(temp, "Lives: %d",lives);

#ifdef WINDOWS
	RECT rct;
	rct.left=2; //2
	rct.right=780;
	rct.top=10; //10
	rct.bottom=rct.top+20;
	sprite_handler->End();
	m_font->DrawText(NULL, temp , -1, &rct, 0, fontColor ); //working print
	//m_font->DrawText(NULL, "iLives", -1, &rct, 0, fontColor ); //lives referance
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
#endif

#ifdef SDL
	RenderText(2,5, temp);
#endif

	return iLives;	

}
int Player::RenderScore()
{	
	char temp[30];
	int score = GetScore();
	sprintf(temp, "Score: %d",score);
#ifdef WINDOWS
	sprite_handler->End();
	RECT rct;
	rct.left=2; //2
	rct.right=780;
	rct.top=30; //10
	rct.bottom=rct.top+20;
	m_font->DrawText(NULL, temp , -1, &rct, 0, fontColor ); //working print
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);

#endif

#ifdef SDL
	RenderText(2,30, temp);
#endif
	return iScore;	

}
int Player::RenderBombs()
{	
	char temp[18];
	int ibombs = GetBombs();
	sprintf(temp, "Bombs: %d",ibombs);

#ifdef WINDOWS
	sprite_handler->End();
	RECT rct;
	rct.left=2; //2
	rct.right=780;
	rct.top=50; //10
	rct.bottom=rct.top+20;

	m_font->DrawText(NULL, temp , -1, &rct, 0, fontColor ); //working print
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);


#endif
#ifdef SDL
	RenderText(2,55, temp);
#endif
	return iBombs;	


}
void Player::Move()
{
	static int NumB = 0;
#ifdef SDL
	Uint8 *keystates = SDL_GetKeyState( NULL );


	if(keystates[SDLK_UP] || keystates[SDLK_w])sUnit.movey -= 5;
	if(keystates[SDLK_DOWN] || keystates[SDLK_s])sUnit.movey += 5;
	if(keystates[SDLK_LEFT] || keystates[SDLK_a])sUnit.movex -= 4;
	if(keystates[SDLK_RIGHT] || keystates[SDLK_d])sUnit.movex += 4;


	if(keystates[SDLK_SPACE])
	{
		if(gameWorld.GetWorldGameClock()->CheckTime(iWeaponTimer, weaponFire))
		{
			if(iWeaponType <= bulletSpriteLv3)
				gameWorld.sound.PlaySpecSound(bullets);
			else /*if(iWeaponType <= laserSpriteLv3)*/
				gameWorld.sound.PlaySpecSound(laser);
			MakeProjectiles();
		}
	}
	if (keystates[SDLK_b])
	{
		if(gameWorld.GetWorldGameClock()->CheckTime(BombDelay, bombFire))
			Bomb();
	}

	//TESTING PURPOSES ONLY. MODIFY KEYSTATE PRESS TO CHECK THINGS
	if(event.type == SDL_KEYDOWN && !keydown )
	{	
		keydown = true;
		if(keystates[SDLK_k])
			if(keystates[SDLK_k]) DecrementLives();
	}
	if(event.type == SDL_KEYUP )keydown = false;

#endif

#ifdef WINDOWS

	if (KEY_DOWN(VK_UP) || KEY_DOWN(VK_W)) sUnit.movey -= 5;
	if (KEY_DOWN(VK_DOWN) || KEY_DOWN(VK_S)) sUnit.movey += 5;
	if (KEY_DOWN(VK_LEFT) || KEY_DOWN(VK_A)) sUnit.movex -= 4;
	if (KEY_DOWN(VK_RIGHT) || KEY_DOWN(VK_D)) sUnit.movex += 4;

	if (KEY_DOWN(VK_SPACE))
	{
		//if((gameWorld.GetWorldGameClock()->GetCounter() % iWeaponTimer) == 0)
		if(gameWorld.GetWorldGameClock()->CheckTime(iWeaponTimer, weaponFire))
		{
			if(iWeaponType <= bulletSpriteLv3)
				gameWorld.sound.PlaySpecSound(bullets);
			else /*if(iWeaponType <= laserSpriteLv3)*/
				gameWorld.sound.PlaySpecSound(laser);
			MakeProjectiles();
		}

	}

	if (KEY_DOWN(VK_K))
		if((gameWorld.GetWorldGameClock()->GetCounter() % 15) == 0 )
			DecrementLives();

	if (KEY_DOWN (VK_B))
		if(gameWorld.GetWorldGameClock()->CheckTime(BombDelay, bombFire))
			Bomb();



#endif
}

void Player::RenderPlayer()
{
	cRender.RenderImage(sUnit);
}

void Player::UpdatePlayer()
{
	//Tim - invulnerabilty time
	if (respawned)
		respawnTime++;

	if(respawnTime == 200 && respawned == true )
	{
		respawnTime = 0;
		respawned = false;
		sUnit.filePath = "Sprites\\MainPlayer.png";
		cRender.LoadImage(sUnit);
	}
	//...................................
	RenderLives();   //update lives to screen
	RenderScore();   //update score to screen
	RenderBombs();   //update # bombs to screen

	if(!Death())
	{
		Move();
		// Move the player left or right
		sUnit.x += sUnit.movex;

		//If the player went too far to the left or right
		if( ( sUnit.x < 0 ) || ( sUnit.x + sUnit.width > SCREEN_WIDTH ) )
		{
			//move back
			sUnit.x -= sUnit.movex;
		}

		//Move the player up or down
		sUnit.y += sUnit.movey;

		//If the player went too far up or down
		if( ( sUnit.y < 0 ) || ( sUnit.y + sUnit.height > SCREEN_HEIGHT ) )
		{
			//move back
			sUnit.y -= sUnit.movey;    
		}

	}
	//Show the player
	RenderPlayer(); 


	for(int i=0; i<GetNumberOfProjectiles(); i++)
	{
		if(!GetProjectile(i)->UpdateWeapon()) RemoveProjectile(i);
	}

	sUnit.movex = 0;
	sUnit.movey = 0;
}

bool Player::Death()
{
	if(died)
	{
		if((gameWorld.GetWorldGameClock()->GetCounter() % sUnit.animdelay) == 0)
		{
			switch(sUnit.curframe)
			{
			case 1:
				sUnit.filePath = "Sprites\\PlayerDeath\\PlayerDeathSprite2.png";
				break;
			case 2:
				sUnit.filePath = "Sprites\\PlayerDeath\\PlayerDeathSprite3.png";
				break;
			case 3:
				sUnit.filePath = "Sprites\\PlayerDeath\\PlayerDeathSprite4.png";
				break;
			case 4:
				sUnit.filePath = "Sprites\\PlayerDeath\\PlayerDeathSprite5.png";
				break;
			case 5:
				sUnit.filePath = "Sprites\\PlayerDeath\\PlayerDeathSprite6.png";
				break;
			case 6:
				sUnit.filePath = "Sprites\\PlayerDeath\\PlayerDeathSprite7.png";
				break;
			case 7:
				sUnit.filePath = "Sprites\\PlayerDeath\\PlayerDeathSprite8.png";
				break;
			case 8:
				sUnit.filePath = "Sprites\\PlayerDeath\\PlayerDeathSprite9.png";
				break;
			case 9:
				sUnit.filePath = "Sprites\\PlayerDeath\\PlayerDeathSprite10.png";
				break;
			case 10:
				sUnit.filePath = "Sprites\\PlayerDeath\\PlayerDeathSprite11.png";
				break;
			case 11:
				sUnit.filePath = "Sprites\\PlayerDeath\\PlayerDeathSprite12.png";
				break;
			case 12:
				sUnit.filePath = "Sprites\\PlayerDeath\\PlayerDeathSprite13.png";
				break;
			case 13:
				cRender.SetUpSprite(sUnit, playerSprite);
				sUnit.filePath = "Sprites\\MainPlayer_Respawn.png";
				died = false;
				respawned = true;

				iWeaponLvl = 0;
				iWeaponType = bulletSpriteLv0;
				iWeaponTimer = BaseWeaponDelay;
				iRocketLvl = 0;
				break;
			}
			cRender.LoadImage(sUnit);
			if(sUnit.curframe == sUnit.animcount) return false;
			sUnit.curframe++;
			sUnit.lastframe++;
		}
		return true;
	}
	return false;
}

void Player::DecrementLives()
{
	if(!died)
	{
		iLives--;
		died = true;
		cRender.SetUpSprite(sUnit, playerDeathSprite);
		sUnit.x -= 16;	//Centers Death Animation Sprites on X axis
		sUnit.y -= 5;	// and Y axis
	}
}
int Player::GetLives()
{
	return iLives;
}
int Player::GetScore()
{
	return iScore;
}
int Player::GetBombs()
{
	return iBombs;
}
void Player::AddScore(int score)
{
	iScore += score;
}

void Player::MakeProjectiles()
{
	if(sUnit.y < 11) return;
	CWeapon* pProjectile = new CWeapon(iWeaponType);

	switch(iWeaponType)
	{
	case bulletSpriteLv0:
		pProjectile->Fire();
		AddProjectile(pProjectile);

		break;
	case bulletSpriteLv1:
		pProjectile->Fire();
		pProjectile->ModPosition(-8,0);
		AddProjectile(pProjectile);

		pProjectile = new CWeapon(iWeaponType);
		pProjectile->Fire();
		pProjectile->ModPosition(8,0);
		AddProjectile(pProjectile);
		break;
	case bulletSpriteLv2:
		pProjectile->Fire();
		AddProjectile(pProjectile);

		pProjectile = new CWeapon(iWeaponType);
		pProjectile->Fire();
		pProjectile->SetX(-5);
		AddProjectile(pProjectile);

		pProjectile = new CWeapon(iWeaponType);
		pProjectile->Fire();
		pProjectile->SetX(5);
		AddProjectile(pProjectile);
		break;
	case bulletSpriteLv3:
		pProjectile->Fire();
		AddProjectile(pProjectile);

		pProjectile = new CWeapon(iWeaponType);
		pProjectile->Fire();
		pProjectile->SetX(3);
		AddProjectile(pProjectile);

		pProjectile = new CWeapon(iWeaponType);
		pProjectile->Fire();
		pProjectile->SetX(6);
		AddProjectile(pProjectile);

		pProjectile = new CWeapon(iWeaponType);
		pProjectile->Fire();
		pProjectile->SetX(-3);
		AddProjectile(pProjectile);

		pProjectile = new CWeapon(iWeaponType);
		pProjectile->Fire();
		pProjectile->SetX(-6);
		AddProjectile(pProjectile);
		break;
	case laserSpriteLv1:
		pProjectile->Fire();
		AddProjectile(pProjectile);
		break;
	case laserSpriteLv2:
		pProjectile->Fire();
		pProjectile->ModPosition(-5,0);
		AddProjectile(pProjectile);

		pProjectile = new CWeapon(iWeaponType);
		pProjectile->Fire();
		pProjectile->ModPosition(5,0);
		AddProjectile(pProjectile);
		break;
	case laserSpriteLv3:
		pProjectile->Fire();
		AddProjectile(pProjectile);
		break;
	}

	if(gameWorld.GetWorldGameClock()->CheckTime(RocketDelay, rocketFire))
	{
		CWeapon *pRocket = new CWeapon;
		switch(iRocketLvl)
		{
		case 0:
			break;
		case 1:
			pRocket = new CWeapon(rocketSpriteLv1);
			pRocket->Fire();
			AddProjectile(pRocket);
			break;
		case 2:
			pRocket = new CWeapon(rocketSpriteLv2);
			pRocket->Fire();
			pRocket->ModPosition(-13,5);
			AddProjectile(pRocket);

			pRocket = new CWeapon(rocketSpriteLv2);
			pRocket->Fire();
			pRocket->ModPosition(13,5);
			AddProjectile(pRocket);
			break;
		case 3:
			pRocket = new CWeapon(rocketSpriteLv3);
			pRocket->Fire();
			pRocket->ModPosition(-13,5);
			AddProjectile(pRocket);

			pRocket = new CWeapon(rocketSpriteLv3);
			pRocket->Fire();
			pRocket->ModPosition(13,5);
			AddProjectile(pRocket);

			pRocket = new CWeapon(rocketSpriteLv3);
			pRocket->Fire();
			pRocket->ModPosition(-26,10);
			AddProjectile(pRocket);

			pRocket = new CWeapon(rocketSpriteLv3);
			pRocket->Fire();
			pRocket->ModPosition(26,10);
			AddProjectile(pRocket);
			break;
		}
	}
}

void Player::AddProjectile(CWeapon* Projectile)
{
	ProjectileList.Add((void*) Projectile);
}

CWeapon *Player::GetProjectile(int i)
{
	return (CWeapon*)ProjectileList.Get(i);
}

int Player::GetNumberOfProjectiles()
{
	return ProjectileList.ListSize();
}

void Player::RemoveProjectile(int i)
{
	ProjectileList.Remove(i);
}

void Player::CollectedPowerup(int PowerupType)
{
	iWeaponLvl++;

	switch(iWeaponLvl)
	{

	case 1: 
		if(PowerupType == kBullets){iWeaponType = bulletSpriteLv1; iWeaponTimer = BulletDelay;}
		if(PowerupType == kLaser){iWeaponType = laserSpriteLv1; iWeaponTimer = LaserLv1Delay;}
		break;
	case 2: 
		if(PowerupType == kBullets){iWeaponType = bulletSpriteLv2; iWeaponTimer = BulletDelay;}
		if(PowerupType == kLaser){iWeaponType = laserSpriteLv2; iWeaponTimer = LaserLv1Delay;}
		break;
	case 3: 
		if(PowerupType == kBullets){iWeaponType = bulletSpriteLv3; iWeaponTimer = BulletDelay;}
		if(PowerupType == kLaser){iWeaponType = laserSpriteLv3; iWeaponTimer = LaserLv3Delay;}
		break;
	default:
		iScore += 1000;
		if(PowerupType == kBullets){iWeaponType = bulletSpriteLv3; iWeaponTimer = BulletDelay;}
		if(PowerupType == kLaser){iWeaponType = laserSpriteLv3; iWeaponTimer = LaserLv3Delay;}
		break;

	}

	if(PowerupType == kRockets)
	{
		iWeaponLvl--;
		if(iRocketLvl < 3)
			iRocketLvl++;
	}

}
bool Player::isAlive()
{
	if(died)
		return false;
	else
		return true;
}

bool Player::isRespawned()
{
	return respawned;
}
int Player::Bomb()
{
	static SPRITE Bomb = cRender.SetUpSprite(Bomb, BombSprite);

	if (iBombs>0)
	{
		gameWorld.Bombs();

		cRender.RenderImage(Bomb);

		iBombs--;
	}

	return iBombs;
}