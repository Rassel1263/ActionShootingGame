#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos) : Unit(pos)
{
	enemyDir = EnemyDir::IDLE_LEFT;
	behavior = EnemyBehavior::IDLE;

	EnemyIdle::GetInstance()->EnterState(this);
}

void CEnemy::Update(float deltaTime)
{
	SetEnemyDir();

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

bool CEnemy::Move(float deltaTime)
{
	if (GetDistanceFromTarget(static_cast<GameScene*>(nowScene)->player->pos) > playerDetectionRange * playerDetectionRange)
	{
		pos += GetDirectionFromPlayer() * ability.speed * deltaTime;
		return true;
	}

	return false;
}

void CEnemy::SetEnemyDir()
{
	D3DXVECTOR2 dir = GetDirectionFromPlayer();

	if (behavior == EnemyBehavior::IDLE)
	{
		if (dir.y > 0.6) enemyDir = EnemyDir::IDLE_UP;
		else
			(dir.x > 0) ? enemyDir = EnemyDir::IDLE_RIGHT : enemyDir = EnemyDir::IDLE_LEFT;
	}

	if (behavior == EnemyBehavior::WALK)
	{
		if (dir.y > 0.6) enemyDir = EnemyDir::WALK_UP;
		else
			(dir.x > 0) ? enemyDir = EnemyDir::WALK_RIGHT: enemyDir = EnemyDir::WALK_LEFT;
	}
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

D3DXVECTOR2 CEnemy::GetDirectionFromPlayer()
{
	D3DXVECTOR2 distance = static_cast<GameScene*>(nowScene)->player->pos - pos;
	D3DXVec2Normalize(&distance, &distance);

	return distance;
;}

Sprite& CEnemy::GetNowSprite()
{
	return enemySprites.at(enemyDir);
}
