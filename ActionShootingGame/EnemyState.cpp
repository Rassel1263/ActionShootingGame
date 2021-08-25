#include "Header.h"

EnemyIdle* EnemyIdle::GetInstance()
{
	static EnemyIdle instance;
	return &instance;
}

void EnemyIdle::EnterState(CEnemy* obj)
{
	obj->behavior = CEnemy::EnemyBehavior::IDLE;
}

void EnemyIdle::UpdateState(CEnemy* obj, float deltaTime)
{
	if (obj->Move(deltaTime))
	{
		obj->SetState(EnemyWalk::GetInstance());
		return;
	}

	if (obj->behavior == CEnemy::EnemyBehavior::HIT)
	{
		obj->SetState(EnemyHit::GetInstance());
		return;
	}
}

void EnemyIdle::ExitState(CEnemy* obj)
{
}

EnemyWalk* EnemyWalk::GetInstance()
{
	static EnemyWalk instance;
	return &instance;
}

void EnemyWalk::EnterState(CEnemy* obj)
{
	obj->behavior = CEnemy::EnemyBehavior::WALK;

	obj->SetEnemyImage();
	obj->GetNowSprite().Reset();
}

void EnemyWalk::UpdateState(CEnemy* obj, float deltaTime)
{
	if (!obj->Move(deltaTime))
	{
		obj->SetState(EnemyIdle::GetInstance());
		return;
	}

	if (obj->behavior == CEnemy::EnemyBehavior::HIT)
	{
		obj->SetState(EnemyHit::GetInstance());
		return;
	}
}

void EnemyWalk::ExitState(CEnemy* obj)
{
}

EnemyHit* EnemyHit::GetInstance()
{
	static EnemyHit instance;
	return &instance;
}

void EnemyHit::EnterState(CEnemy* obj)
{
	obj->ability.hp -= obj->hitDamage;
	obj->behavior = CEnemy::EnemyBehavior::HIT;

	obj->SetEnemyImage();
	obj->GetNowSprite().Reset();
}

void EnemyHit::UpdateState(CEnemy* obj, float deltaTime)
{
	if (obj->ability.hp <= 0.0f)
	{
		obj->SetState(EnemyDie::GetInstance());
		return;
	}

	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(EnemyIdle::GetInstance());
		return;
	}
}

void EnemyHit::ExitState(CEnemy* obj)
{
}

EnemyDie* EnemyDie::GetInstance()
{
	static EnemyDie instance;
	return &instance;
}

void EnemyDie::EnterState(CEnemy* obj)
{
	obj->behavior = CEnemy::EnemyBehavior::DIE;
	obj->bCollider = false;
	obj->SetEnemyImage();
}

void EnemyDie::UpdateState(CEnemy* obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation)
	{
		timer -= deltaTime;

		if (timer <= 0.0)
		{
			obj->Die();
		}
	}
}

void EnemyDie::ExitState(CEnemy* obj)
{
	timer = 0.3f;
}
