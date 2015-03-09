#include "Enemy.h"
#include "World.h"
extern RenderMachine cRender;
extern World gameWorld;

Enemy::Enemy(){
	steps = 40;
	if (iState != boss)
		iState = norm;
	else
		iState = boss;
	died = false;
	doneDying = false;
}

Enemy::~Enemy(){
	#ifdef SDL
		SDL_FreeSurface(sUnit.unitSprite);
	#endif
	#ifdef WINDOWS
		sUnit.unitSprite = NULL;
	#endif
}

void Enemy::Attack()
{
	if(iState != boss)
	{
		//if(gameWorld.GetWorldGameClock()->GetCounter() % 50 == 0)
		if(gameWorld.GetWorldGameClock()->CheckTime(1000,enemyFire))
		{
			CWeapon *temp = new CWeapon(enemyBulletSprite);
			temp->Fire();
			temp->SetPositionForEnemy((sUnit.x + (sUnit.width/2)), (sUnit.y + (sUnit.height/2)));

			//temp->SetY(((projY - sUnit.y) / 60));
			//temp->SetX(((projX - sUnit.x) / 60));

			int tempnum = ((((projX - sUnit.x)*(projX - sUnit.x)) + ((projY - sUnit.y)*(projY - sUnit.y))) / (58*58));

			if(tempnum == 0)
				tempnum = 1;

			int tempx = (projX - sUnit.x) / tempnum;
			int tempy = (projY - sUnit.y) / tempnum;

			if( (tempx == 0 && tempy == 0) )
			{
				if(projX < sUnit.x)
					tempx = -1;
				else
					tempx = 1;
				if(projY < sUnit.y)
					tempy = -1;
				else
					tempy = 1;
			}
			if( tempx > 6 || tempx < -6 )
			{
				if(projX < sUnit.x)
					tempx = -2;
				else
					tempx = 2;
			}
			if( tempy > 6 || tempy < -6 )
			{
				if(projY < sUnit.y)
					tempy = -2;
				else
					tempy = 2;
			}

			temp->SetY(tempy);
			temp->SetX(tempx);
			AddProjectile(temp); /*(void*)*/
		}
	}
	else /*boss*/
	{
		if (gameWorld.GetWorldGameClock()->CheckTime(1000,enemyFire)){
			Enemy *temp = new Enemy();
			temp->createBasic(1);
			temp->sUnit.y += sUnit.height;
			Boss_Firing.Add(temp);
		}
	}

}

void Enemy::createBasic(int type){

	sUnit.y = 0;
	sUnit.x = (rand() % SCREEN_WIDTH);
	if (GetSpriteImage(type)){
		GetPlayer();
	}
	// enemy  doesn't spawn or attack to early.
	if (sUnit.x <= 0) sUnit.x += 5;
	if (sUnit.x + sUnit.width >= SCREEN_WIDTH) sUnit.x = SCREEN_WIDTH - sUnit.width;
	if (targetY <= SCREEN_HEIGHT/2 && past==0){
		targetY -= (SCREEN_HEIGHT/2);
	}
}

bool Enemy::GetSpriteImage(int type){
	iState = norm;
	// RenderMachine:type = enemy_Dart
	if (type == 1){
		cRender.SetUpSprite(sUnit, enemy_Dart);
		past = 0;
		iHealth = type * gameWorld.GetLevel()->GetCurrentLevel();
		score = 200;
		steps = 20;
		return true;
	}
	// RenderMachine:type = enemy_Scooter
	if (type == 2){
		cRender.SetUpSprite(sUnit, enemy_Scooter);
		past = 0;
		iHealth = type * gameWorld.GetLevel()->GetCurrentLevel();
		score = 300;
		steps = 30;
		return true;
	}
	// RenderMachine:type = enemy_Tank
	if (type == 3){
		cRender.SetUpSprite(sUnit, enemy_Tank);
		past = 0;
		iHealth = type * gameWorld.GetLevel()->GetCurrentLevel();
		score = 700;
		steps = 70;
		return true;
	}
	// RenderMachine:type = enemy_Pincer
	if (type == 4){
		cRender.SetUpSprite(sUnit, enemy_Pincer);
		past = 0;
		iHealth = /*type*/ 1 * gameWorld.GetLevel()->GetCurrentLevel();
		score = 200;
		steps = 20;
		return true;
	}
	// RenderMachine:type = enemy_Skiffy.  Mini Boss - They do pretty much the same thing
	if (type == 5){
		iState = miniBoss;
		cRender.SetUpSprite(sUnit, enemy_Skiffy);
		past = 0;
		iHealth = type * gameWorld.GetLevel()->GetCurrentLevel();
		score = 1000;
		steps = 100;
		return true;
	}
	// RenderMachine:type = enemy_Warbird.  Mini Boss - They do pretty much the same thing
	if (type == 6){
		iState = miniBoss;
		cRender.SetUpSprite(sUnit, enemy_Warbird);
		past = 0;
		iHealth = type * gameWorld.GetLevel()->GetCurrentLevel();
		score = 1000;
		steps = 100;
		return true;
	}
	// RenderMachine:type = boss_Level1
	if (type == 7){
		iState = boss;
		cRender.SetUpSprite(sUnit, boss_Lvl1);
		sUnit.x = (SCREEN_WIDTH / 2) - (sUnit.width / 2);
		sUnit.y = 0;
		iHealth = type * 10 * gameWorld.GetLevel()->GetCurrentLevel();
		score = 10000;
		steps = 100;
		past = 1;
		xMove = 1;
		yMove = 1;
		return true;
	}

	return false;
}

void Enemy::UpdateEnemy(){

	if(!EnemyDeath())
	{
		if (iState == boss){
			BossUpdate();

		}else {
			if (sUnit.y + sUnit.height + steps >= targetY && past == 0){
				this->GetPlayer();
				if (targetY > SCREEN_HEIGHT / 2){
					targetY -= SCREEN_HEIGHT / 1.5;
				}
				past++;
			}
			if (sUnit.y <= targetY + steps && past == 1){
				targetY = SCREEN_HEIGHT;
				past++;
			}

			MoveToPosition();
			Physics();
		}
		GetPlayerXY();

		// if the target equals to a negative number
		if (targetY < 0){
			targetY = abs(targetY);
		}
		Attack();
	}
	UpdateEnemyWeapons();
	Render();
}

void Enemy::BossUpdate(){

	for (int n = 0; n < Boss_Firing.ListSize(); n++){
		Enemy* temp = (Enemy*) this->Boss_Firing.Get(n);
		if (temp->IsDoneDying())
		{
			Boss_Firing.Remove(n);
		}
		else{
			temp->UpdateEnemy();
			Attack();
			
		}
	}
	UpdateEnemyWeapons();
}

void Enemy::MoveToPosition(){
	if (iState == norm){
		sUnit.y += (targetY - sUnit.y) / steps;
		sUnit.x += (targetX - sUnit.x) / steps;
	}

	if (iState == miniBoss){
		sUnit.y += (targetY - sUnit.y) / steps;
	}
}

void Enemy::Physics(){
	/*===================================================================================
	Screen collision: top and bottom
	//===================================================================================*/
	if (sUnit.y < 0 || sUnit.y + sUnit.height < 0){
		sUnit.y = 5;
	}
	if (EndOfScreen()){
		iHealth = 0;
	}

	if (sUnit.x < -1){
		sUnit.x = 0;
	}

	if (sUnit.x + sUnit.width >= SCREEN_WIDTH){
		sUnit.x -= 5;
	}
}

bool Enemy::EndOfScreen(){
	if (sUnit.y + steps > SCREEN_HEIGHT || sUnit.y + sUnit.height + steps> SCREEN_HEIGHT)
		return true;
	return false;
}
void Enemy::Render(){
	cRender.RenderImage(sUnit);
}

void Enemy::GetPlayer(){
	target = &gameWorld.GetPlayerSprite();
	targetX = target->x;
	targetY = target->y;

	// the player is at the top of screen
	if (targetY < 0){
		targetY = 5;
	}
}

void Enemy::GetPlayerXY()
{
	target = &gameWorld.GetPlayerSprite();
	projX = target->x + (target->width/2);
	projY = target->y + (target->height/2);
}

void Enemy::SetEnemyDied(bool Died)
{
	gameWorld.sound.PlaySpecSound(1);
	died = Died;
	if (iState == boss){
		cRender.SetUpSprite(sUnit, bossDeathSprite);
	} else{
		cRender.SetUpSprite(sUnit, enemyDeathSprite);
	}
}

bool Enemy::EnemyDeath()
{
	if(died)
	{
		if((gameWorld.GetWorldGameClock()->GetCounter() % sUnit.animdelay) == 0)
		{
			switch(sUnit.curframe)
			{
			case 1:
				if (iState == boss){
					sUnit.filePath = "Sprites\\EnemyDeath\\BossDeathSprite2.png";
				}else {
					sUnit.filePath = "Sprites\\EnemyDeath\\EnemyDeathSprite2.png";
				}
				break;
			case 2:
				if (iState == boss){
					sUnit.filePath = "Sprites\\EnemyDeath\\BossDeathSprite3.png";
				}else {
					sUnit.filePath = "Sprites\\EnemyDeath\\EnemyDeathSprite3.png";
				}
				break;
			case 3:
				if (iState == boss){
					sUnit.filePath = "Sprites\\EnemyDeath\\BossDeathSprite4.png";
				}else {
					sUnit.filePath = "Sprites\\EnemyDeath\\EnemyDeathSprite4.png";
				}
				break;
			case 4:
				if (iState == boss){
					sUnit.filePath = "Sprites\\EnemyDeath\\BossDeathSprite5.png";
				}else {
					sUnit.filePath = "Sprites\\EnemyDeath\\EnemyDeathSprite5.png";
				}
				break;
			case 5:
				doneDying = true;
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

bool Enemy::IsDoneDying()
{
	return doneDying;
}
bool Enemy::IsDead()
{
	return died;
}

void Enemy::UpdateEnemyWeapons()
{
	for(int i=0; i<GetNumberOfProjectiles(); i++)
	{
		if(!GetProjectile(i)->UpdateWeapon())RemoveProjectile(i);
	}
}

void Enemy::DestoryEnemy()
{
#ifdef SDL
	SDL_FreeSurface(sUnit.unitSprite);
#endif
#ifdef WINDOWS
	sUnit.unitSprite = NULL;
#endif
	eProjectileList.Clear();
}

void Enemy::AddProjectile(CWeapon* Projectile)
{
	eProjectileList.Add((void*) Projectile);
}

CWeapon *Enemy::GetProjectile(int i)
{
	return (CWeapon*)eProjectileList.Get(i);
}

int Enemy::GetNumberOfProjectiles()
{
	return eProjectileList.ListSize();
}

void Enemy::RemoveProjectile(int i)
{
	eProjectileList.Remove(i);
}