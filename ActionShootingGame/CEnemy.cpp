#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos) : Unit(pos)
{
	nowScene->obm.AddObject(new CEffect(L"Spawn/after", pos, 0.05f));

	enemyImage = EnemyImage::IDLE_LEFT;
	behavior = EnemyBehavior::IDLE;

	poisonShader = new ColorShader();
}

CEnemy::~CEnemy()
{
	if (gun)
		gun->destroy = true;

	nowScene->SortEnemyVector(this);
}

void CEnemy::Update(float deltaTime)
{
	SetEnemyImage();

	if (poison)
	{
		poisonTime -= deltaTime;
		tickTime -= deltaTime;

		if (tickTime <= 0.0f)
		{
			behavior = EnemyBehavior::HIT;
			hitDamage = 1;
			tickTime = 1.0f;
		}
		
		if (poisonTime <= 0.0f)
		{
			poisonTime = 2.0f;
			poison = false;
		}
	}

	if (behavior != EnemyBehavior::HIT && behavior != EnemyBehavior::DIE)
		if (CheckDistanceToPlayer(playerDetectionRange))
			EnemyAttack(deltaTime);

	if (nowState)
		nowState->UpdateState(this, deltaTime);

	GetNowSprite().Update(deltaTime);
	Unit::Update(deltaTime);
}

void CEnemy::Render()
{
	renderInfo.pos = pos;
	shadow.Render(RenderInfo{ D3DXVECTOR2(pos.x, pos.y + 1) });

	if (poison)
		poisonShader->Render(poisonShader, GetNowSprite(), renderInfo, D3DXVECTOR4(0.25f, 0.35f, 0.2f, 0.0f));
	else
		GetNowSprite().Render(renderInfo);

	Unit::Render();
}

void CEnemy::OnCollision(Collider& coli)
{

	if (coli.tag == L"allyBullet")
	{
		hitDamage = static_cast<CBullet*>(coli.obj)->damage;

		D3DXVECTOR2 dir = pos - coli.obj->pos;
		D3DXVec2Normalize(&dir, &dir);

		force += D3DXVECTOR2(dir.x, dir.y) * 10;

		if (behavior != EnemyBehavior::HIT)
			behavior = EnemyBehavior::HIT;
	}
}

bool CEnemy::Move(float deltaTime)
{
	if (!CheckDistanceToPlayer(stopRange))
	{
		pos += GetDirectionFromPlayer() * ability.speed * deltaTime;
		return true;
	}

	return false;
}

void CEnemy::Die()
{
	std::default_random_engine rnd(nowScene->rd());
	std::uniform_int_distribution<int> dis(0, 4);

	nowScene->obm.AddObject(new CEffect(L"Boom", pos + D3DXVECTOR2(0, 20), 0.05f ));
	if (!dis(rnd))
		nowScene->obm.AddObject(new Item(pos));

	nowScene->AddScore(rand() % 200 + 100);
	destroy = true;
}

void CEnemy::SetEnemyImage()
{
	D3DXVECTOR2 dir = GetDirectionFromPlayer();

	if (behavior == EnemyBehavior::IDLE)
	{
		if (dir.y > 0.6) enemyImage = EnemyImage::IDLE_UP;
		else
			(dir.x > 0) ? enemyImage = EnemyImage::IDLE_RIGHT : enemyImage = EnemyImage::IDLE_LEFT;
	}

	if (behavior == EnemyBehavior::WALK)
	{
		if (dir.y > 0.6) enemyImage = EnemyImage::WALK_UP;
		else
			(dir.x > 0) ? enemyImage = EnemyImage::WALK_RIGHT : enemyImage = EnemyImage::WALK_LEFT;
	}

	if (behavior == EnemyBehavior::HIT)
		enemyImage = EnemyImage::HIT;

	if (behavior == EnemyBehavior::DIE)
		enemyImage = EnemyImage::DIE;
}

void CEnemy::SetState(CState<CEnemy>* nextState)
{
	if (nowState)
		nowState->ExitState(this);

	nowState = nextState;
	nowState->EnterState(this);
}

void CEnemy::SetGunPos()
{
	D3DXVECTOR2 dir = GetDirectionFromPlayer();

	float gunScale = (dir.x > 0) ? 1 : -1;
	float degree = D3DXToDegree(atan2(-dir.y, dir.x));

	gun->gunRI.rotate = degree;
	gun->gunRI.scale.y = gunScale;
	gun->pos = pos + D3DXVECTOR2(5 * gunScale, 7);
}

Sprite& CEnemy::GetNowSprite()
{
	return enemySprites.at(enemyImage);
}

void CEnemy::EnemyAttack(float deltaTime)
{
	restTimer += deltaTime;

	if (restTimer > ability.attackSpeed)
		gun->gunSpr.Update(deltaTime);

	if (!gun->gunSpr.bAnimation)
	{
		float angle = D3DXToDegree(atan2(GetDirectionFromPlayer().y, GetDirectionFromPlayer().x));

		restTimer = 0.0f;
		gun->Shoot(angle, ability.attackPower, team);
		gun->gunSpr.Reset();
	}
}
