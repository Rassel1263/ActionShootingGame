#include "Header.h"

BossIdle* BossIdle::GetInstance()
{
	static BossIdle instance;
	return &instance;
}

void BossIdle::EnterState(CBoss* obj)
{
	obj->behavior = CBoss::BossBehavior::IDLE;

	obj->SetBossImage();
	obj->GetNowSprite().Reset();
}

void BossIdle::UpdateState(CBoss* obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		obj->SetState(BossDie::GetInstance());
		return;
	}

	obj->restTime -= deltaTime;

	if (obj->restTime <= 0.0f)
	{
		std::random_device rd;
		std::default_random_engine rnd(rd());
		std::uniform_int_distribution<int> dis(1, 3);

		obj->behavior = CBoss::BossBehavior::ATTACK;
		int patternIdx = dis(rnd);
		obj->SetPattern(patternIdx);

		switch (patternIdx)
		{
		obj->SetPattern(patternIdx);
		case 1:
			obj->SetState(BossPattern1::GetInstance());
			return;
		case 2:
			obj->SetState(BossPattern2::GetInstance());
			return;
		case 3:
			obj->SetState(BossPattern3::GetInstance());
			return;
		}
	}

	if(obj->bossIndex == 1)
	if (obj->Move(deltaTime))
	{
		obj->SetState(BossWalk::GetInstance());
		return;
	}
}

void BossIdle::ExitState(CBoss* obj)
{
	obj->restTime = 1.0f;
}

BossWalk* BossWalk::GetInstance()
{
	static BossWalk instance;
	return &instance;
}

void BossWalk::EnterState(CBoss* obj)
{
	obj->behavior = CBoss::BossBehavior::WALK;

	obj->SetBossImage();
	obj->GetNowSprite().Reset();
}

void BossWalk::UpdateState(CBoss* obj, float deltaTime)
{
	std::cout << obj->GetNowSprite().scene << std::endl;

	if (obj->ability.hp <= 0)
	{
		obj->SetState(BossDie::GetInstance());
		return;
	}

	obj->restTime -= deltaTime;

	if (obj->restTime <= 0.0f)
	{
		std::random_device rd;
		std::default_random_engine rnd(rd());
		std::uniform_int_distribution<int> dis(1, 3);

		int patternIdx = dis(rnd);
		obj->SetPattern(patternIdx);

		switch (patternIdx)
		{
		case 1:
			obj->SetState(BossPattern1::GetInstance());
			return;
		case 2:
			obj->SetState(BossPattern2::GetInstance());
			return;
		case 3:
			obj->SetState(BossPattern3::GetInstance());
			return;

		}
	}

	if (!obj->Move(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossWalk::ExitState(CBoss* obj)
{
}

BossPattern1* BossPattern1::GetInstance()
{
	static BossPattern1 instance;
	return &instance;
}

void BossPattern1::EnterState(CBoss* obj)
{
	obj->SetBossImage();
	obj->GetNowSprite().Reset();
}

void BossPattern1::UpdateState(CBoss* obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		obj->SetState(BossDie::GetInstance());
		return;
	}

	if (!obj->Pattern1(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossPattern1::ExitState(CBoss* obj)
{
}

BossPattern2* BossPattern2::GetInstance()
{

	static BossPattern2 instance;
	return &instance;
}

void BossPattern2::EnterState(CBoss* obj)
{
	obj->SetBossImage();
	obj->GetNowSprite().Reset();
}

void BossPattern2::UpdateState(CBoss* obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		obj->SetState(BossDie::GetInstance());
		return;
	}

	if (!obj->Pattern2(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossPattern2::ExitState(CBoss* obj)
{
}

BossPattern3* BossPattern3::GetInstance()
{

	static BossPattern3 instance;
	return &instance;
}

void BossPattern3::EnterState(CBoss* obj)
{
	obj->SetBossImage();
	obj->GetNowSprite().Reset();
}

void BossPattern3::UpdateState(CBoss* obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		obj->SetState(BossDie::GetInstance());
		return;
	}

	if (!obj->Pattern3(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossPattern3::ExitState(CBoss* obj)
{
}

BossDie* BossDie::GetInstance()
{
	static BossDie instance;
	return &instance;
}

void BossDie::EnterState(CBoss* obj)
{
	nowScene->bossZoom = true;
	Camera::GetInstance().destCameraPos = { obj->pos + D3DXVECTOR2(0, 50) };

	obj->behavior = CBoss::BossBehavior::DIE;
	obj->bCollider = false;
	obj->ability.hp = 0;
	obj->poison = false;
	obj->SetBossImage();
}

void BossDie::UpdateState(CBoss* obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation)
	{
		timer -= deltaTime;

		if (timer <= 0.0f)
		{
			obj->Die();
			timer = 2.0f;
			return;
		}
	}
}

void BossDie::ExitState(CBoss* obj)
{
}
