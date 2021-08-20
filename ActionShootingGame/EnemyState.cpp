#include "Header.h"

EnemyIdle* EnemyIdle::GetInstance()
{
	static EnemyIdle instance;
	return &instance;
}

void EnemyIdle::EnterState(CEnemy* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;
	obj->behavior = CEnemy::EnemyBehavior::IDLE;
}

void EnemyIdle::UpdateState(CEnemy* obj, float deltaTime)
{
	if (obj->Move(deltaTime))
	{
		EnemyWalk::GetInstance()->EnterState(obj);
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
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;
	obj->behavior = CEnemy::EnemyBehavior::WALK;

	obj->SetEnemyDir();
	obj->GetNowSprite().Reset();
}

void EnemyWalk::UpdateState(CEnemy* obj, float deltaTime)
{
	std::cout << obj->GetNowSprite().scene << std::endl;

	if (!obj->Move(deltaTime))
	{
		EnemyIdle::GetInstance()->EnterState(obj);
		return;
	}
}

void EnemyWalk::ExitState(CEnemy* obj)
{
}
