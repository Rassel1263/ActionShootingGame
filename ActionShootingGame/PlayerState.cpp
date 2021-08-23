#include "Header.h"

PlayerIdle* PlayerIdle::GetInstance()
{
	static PlayerIdle instance;
	return &instance;
}

void PlayerIdle::EnterState(Player* obj)
{
	obj->behavior = Player::PlayerBehavior::IDLE;
}

void PlayerIdle::UpdateState(Player* obj, float deltaTime)
{
	if (obj->Move(deltaTime))
	{
		obj->SetState(PlayerWalk::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyPress(VK_LBUTTON))
	{
		obj->SetState(PlayerShoot::GetInstance());
		return;
	}
}

void PlayerIdle::ExitState(Player* obj)
{
}


PlayerWalk* PlayerWalk::GetInstance()
{
	static PlayerWalk instance;
	return &instance;
}

void PlayerWalk::EnterState(Player* obj)
{
	obj->behavior = Player::PlayerBehavior::WALK;
}

void PlayerWalk::UpdateState(Player* obj, float deltaTime)
{
	if (Input::GetInstance().KeyDown(VK_RBUTTON))
	{
		obj->SetState(PlayerDodgeRoll::GetInstance());
		return;
	}

	if (!obj->Move(deltaTime))
	{
		obj->SetState(PlayerIdle ::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyPress(VK_LBUTTON))
	{
		obj->SetState(PlayerShoot::GetInstance());
		return;
	}
}

void PlayerWalk::ExitState(Player* obj)
{
}

PlayerDodgeRoll* PlayerDodgeRoll::GetInstance()
{
	static PlayerDodgeRoll instance;
	return &instance;
}

void PlayerDodgeRoll::EnterState(Player* obj)
{
	obj->behavior = Player::PlayerBehavior::ROLL;

	holdWeapon = obj->holdWeapon;
	obj->holdWeapon = false;

	D3DXVECTOR2 dir = { 0, 0 };
	D3DXVec2Normalize(&dir, &obj->moveDir);

	obj->SetNotHoldGunPlayerDir(obj->moveDir);

	obj->velocity = dir * 250;
	obj->GetNowSprite().Reset();
}

void PlayerDodgeRoll::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}
}

void PlayerDodgeRoll::ExitState(Player* obj)
{
	obj->holdWeapon = holdWeapon;
	holdWeapon = false;
}

PlayerShoot* PlayerShoot::GetInstance()
{
	static PlayerShoot instance;
	return &instance;
}

void PlayerShoot::EnterState(Player* obj)
{
	 obj->gun->Shoot(nowScene->mouse->GetMouseAngleToDegree(false, obj->pos), 1, obj->team);
	obj->gun->gunSpr.scene = 1;
}

void PlayerShoot::UpdateState(Player* obj, float deltaTime)
{
	timer += deltaTime;

	if (timer > obj->ability.attackSpeed / 2.0f)
		obj->gun->gunSpr.Reset();

	if (timer > obj->ability.attackSpeed)
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}
}

void PlayerShoot::ExitState(Player* obj)
{
	obj->gun->gunSpr.Reset();
	timer = 0.0f;
}
