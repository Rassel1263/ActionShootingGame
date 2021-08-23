#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos) : Unit(pos)
{
	nowScene->obm.AddObject(new CEffect(L"Spawn/after", pos, 0.05f));

	enemyImage = EnemyImage::IDLE_LEFT;
	behavior = EnemyBehavior::IDLE;

	SetState(EnemyIdle::GetInstance());
}

CEnemy::~CEnemy()
{
	if (gun)
		gun->destroy = true;
}

void CEnemy::Update(float deltaTime)
{
	SetEnemyImage();

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
	GetNowSprite().Render(renderInfo);
	Unit::Render();
}

void CEnemy::OnCollision(Collider& coli)
{
	if (behavior == EnemyBehavior::DIE) return;

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
	nowScene->obm.AddObject(new CEffect(L"Boom", pos + D3DXVECTOR2(0, 20), 0.05f));
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

bool CEnemy::CheckDistanceToPlayer(float detectionRange)
{
	return GetDistanceFromTarget(static_cast<GameScene*>(nowScene)->player->pos) < detectionRange * detectionRange;
}

D3DXVECTOR2 CEnemy::GetDirectionFromPlayer()
{
	if (nowScene->player == NULL)
		return D3DXVECTOR2(0, 0);

	D3DXVECTOR2 distance = nowScene->player->pos - pos;
	D3DXVec2Normalize(&distance, &distance);

	return distance;
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
