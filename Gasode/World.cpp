#include ".\world.h"


#ifdef WINDOWS
extern HWND g_hWnd;
#endif

World::World(void)
{
	numEnemies = 4;
	enemiesOnSrc = 0;
}

World::~World(void)
{
	delete mPlayer;
	delete mLevel;
	delete mGameClock;
}

void World::InitializeWorld()
{
	mGameClock = new GameClock;
	mLevel = new Level;
	mPlayer = new Player;
	mPlayer->Init();
	mLevel->initialize();
	mGameClock->InitGameClock();
	sound.Init();
}
bool World::Update()
{
	if(!mGameClock->Frame())
	{		
		mLevel->Update();
		mPlayer->UpdatePlayer();
		// Renders the enemies based on how many enemies should be on the screen.
		for(int n = 0; n < enemiesOnSrc; n++){
			Enemy* temp = (Enemy*) mEnemies.Get(n);
			if (temp->IsDoneDying())
			{
				mEnemies.Remove(n);
				enemiesOnSrc--;
			}
			else
				temp->UpdateEnemy();
		}
		mPlayer->RenderLives();
		mPlayer->RenderScore();
		mPlayer->RenderBombs();

		//revising powerup generation in the game world - Daniel R - 9/22/06; Revisions: JC, Kai
		for(int i=0; i<mPowerup.ListSize(); i++)
		{
			CPowerup *tempPowerup;
			tempPowerup = (CPowerup*)mPowerup.Get(i);
			tempPowerup->UpdatePowerup();
		}

		CollisionDetection();

		for(int j=0; j < mPowerup.ListSize(); j++)
		{
			CPowerup *tempPowerup;
			tempPowerup = (CPowerup*)mPowerup.Get(j);
			if(IsCollided(mPlayer->GetSprite(), tempPowerup->GetPowerupSprite()))
			{
				mPlayer->CollectedPowerup(tempPowerup->GetPowerupType());
				tempPowerup->TurnPowerupOff();
				mPowerup.Remove(j);
			}
		}
	}
	if(mPlayer->GetLives() <= 0 && mPlayer->isAlive())
		return true;
	if(mLevel->GetCurrentLevel() > MAX_LEVELS)
		return true;

	return false;
}

bool World::IsCollided(SPRITE object, SPRITE spriteCheck2)
{
	if(object.x < spriteCheck2.x +spriteCheck2.width && object.x + object.width > spriteCheck2.x)
	{
		if(object.y < spriteCheck2.y +spriteCheck2.height && object.y + object.height > spriteCheck2.y)
			return true;
	}
	return false;

}
void World::CollisionDetection()
{
	for(int n=0; n < mEnemies.ListSize(); n++)
	{
		Enemy* tempEnemy = (Enemy*)mEnemies.Get(n);
		for(int m=0; m < mPlayer->GetNumberOfProjectiles(); m++)
		{
			SPRITE tempBulletSprite = mPlayer->GetProjectile(m)->GetProjectileSprite();

			if(!tempEnemy->IsDead())
			{
				if(IsCollided(tempBulletSprite, tempEnemy->GetSprite()))
				{ 
					//Removes enemy health based on weapon damage. Returns if unit is dead or not.
					//every enemy creates a powerup
					if(tempEnemy->ChangeHealth(mPlayer->GetProjectile(m)->GetWeaponDamage()))
					{
						if(mEnemies.ListSize() > 0)
							randomEnemy = rand() % 100;
						if(mPowerup.ListSize() < MAX_POWERUP_NUM && randomEnemy < 10)
						{

							CPowerup *tempPowerup = new CPowerup;
							tempPowerup->CreatePowerup(tempEnemy->GetSprite());
							tempPowerup->TurnPowerupOn();
							mPowerup.Add(tempPowerup);
						}
						tempEnemy->SetEnemyDied(true);
						mPlayer->AddScore(tempEnemy->getScore());
					}
					mPlayer->RemoveProjectile(m);
				}
			}
		}
	}


	for(n=0; n < enemiesOnSrc; n++)
	{
		Enemy* tempEnemy = (Enemy*)mEnemies.Get(n);

		if(!tempEnemy->IsDead() && !mPlayer->isRespawned()){

			// checks if the player collides with the enemy
			if(IsCollided(mPlayer->GetSprite(), tempEnemy->GetSprite()) && mPlayer->isAlive())
				mPlayer->DecrementLives();

			// checks if the player is colliding with the enemy bullets
			for(int i=0; i<tempEnemy->GetNumberOfProjectiles(); i++)
			{
				SPRITE tempEnemyBulletSprite = tempEnemy->GetProjectile(i)->GetProjectileSprite();
				if(IsCollided(mPlayer->GetSprite(), tempEnemyBulletSprite) && mPlayer->isAlive())
				{
					mPlayer->DecrementLives();
				}
			}
		}

		// checks if the enemy collides with the end of the screen based on y axis
		if (tempEnemy->EndOfScreen() && tempEnemy->GetState() != boss){
			enemiesOnSrc--;
			mEnemies.Remove(n);
		}

		// boss attacking
		if (tempEnemy->GetState() == boss){
			for(int i = 0; i < tempEnemy->Boss_Firing.ListSize(); i++){
				Enemy* attacker = (Enemy*) tempEnemy->Boss_Firing.Get(i);

				if (attacker->EndOfScreen()){
					tempEnemy->Boss_Firing.Remove(i);
				}
				// checks if the player is colliding with the enemy bullets
				for(int j=0; j<attacker->GetNumberOfProjectiles(); j++)
				{
					SPRITE tempEnemyBulletSprite = attacker->GetProjectile(j)->GetProjectileSprite();
					if(IsCollided(mPlayer->GetSprite(), tempEnemyBulletSprite) && mPlayer->isAlive())
					{
						mPlayer->DecrementLives();
					}
				}

				if (IsCollided(mPlayer->GetSprite(), attacker->GetSprite()) && mPlayer->isAlive()){
					mPlayer->DecrementLives();
				}
				for(int m=0; m < mPlayer->GetNumberOfProjectiles(); m++)
				{
					SPRITE tempBulletSprite = mPlayer->GetProjectile(m)->GetProjectileSprite();

					if(!attacker->IsDead())
					{
						if(IsCollided(tempBulletSprite, attacker->GetSprite()))
						{ 
							//Removes enemy health based on weapon damage. Returns if unit is dead or not.
							//every enemy creates a powerup
							if(attacker->ChangeHealth(mPlayer->GetProjectile(m)->GetWeaponDamage()))
							{
								if(mEnemies.ListSize() > 0)
									randomEnemy = rand() % 100;
								if(mPowerup.ListSize() < MAX_POWERUP_NUM && randomEnemy < 3)
								{

									CPowerup *tempPowerup = new CPowerup;
									tempPowerup->CreatePowerup(attacker->GetSprite());
									tempPowerup->TurnPowerupOn();
									mPowerup.Add(tempPowerup);
								}
								attacker->SetEnemyDied(true);
								mPlayer->AddScore(attacker->getScore());
							}
							mPlayer->RemoveProjectile(m);
						}
					}
				}
			}
		}
	}
}

SPRITE World::GetPlayerSprite()
{
	return mPlayer->GetSprite();
}

SPRITE World::GetEnemySprite(int n)
{
	Enemy* tempEnemy = (Enemy*) mEnemies.Get(n);
	return tempEnemy->GetSprite();
}

GameClock* World::GetWorldGameClock()
{
	return mGameClock;
}

void World::EnemyUpdate(){

	// Renders the enemies based on how many enemies should be on the screen.
	for(int n = 0; n < enemiesOnSrc; n++){
		Enemy* temp = (Enemy*) mEnemies.Get(n);
		if (temp->IsDoneDying())
		{
			//temp->DestoryEnemy();
			mEnemies.Remove(n);
			enemiesOnSrc--;
		}
		else
			temp->UpdateEnemy();
	}
}

void World::Bombs()
{
	sound.PlaySpecSound(2);

	for(int n=0; n < mEnemies.ListSize(); n++)
	{
		Enemy* tempEnemy = (Enemy*)mEnemies.Get(n);

		if(!tempEnemy->IsDead())
		{

			if(tempEnemy->ChangeHealth(3 * mLevel->GetCurrentLevel()))
			{
				if(mEnemies.ListSize() > 0)
					randomEnemy = rand() % 100;
				if(mPowerup.ListSize() < MAX_POWERUP_NUM && randomEnemy < 25)
				{
					CPowerup *tempPowerup = new CPowerup;
					tempPowerup->CreatePowerup(tempEnemy->GetSprite());
					tempPowerup->TurnPowerupOn();
					mPowerup.Add(tempPowerup);
				}
				tempEnemy->SetEnemyDied(true);
				mPlayer->AddScore(tempEnemy->getScore());
			}
		}
	}
}

void World::CreateNewEnemy(int type)
{
	Enemy* temp = new Enemy;
	temp->createBasic(type);
	mEnemies.Add(temp);
	enemiesOnSrc++;
}
Level* World::GetLevel()
{
	return mLevel;
}