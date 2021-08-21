#include "Header.h"

PlayerIdle* PlayerIdle::GetInstance()
{
	static PlayerIdle instance;
	return &instance;
}

void PlayerIdle::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->behavior = Player::PlayerBehavior::IDLE;
}

void PlayerIdle::UpdateState(Player* obj, float deltaTime)
{
	if (obj->Move(deltaTime))
	{
		PlayerWalk::GetInstance()->EnterState(obj);
		return;
	}

	if (Input::GetInstance().KeyPress(VK_LBUTTON))
	{
		PlayerShoot::GetInstance()->EnterState(obj);
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
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->behavior = Player::PlayerBehavior::WALK;
}

void PlayerWalk::UpdateState(Player* obj, float deltaTime)
{
	if (Input::GetInstance().KeyDown(VK_RBUTTON))
	{
		PlayerDodgeRoll::GetInstance()->EnterState(obj);
		return;
	}

	if (!obj->Move(deltaTime))
	{
		PlayerIdle::GetInstance()->EnterState(obj);
		return;
	}

	if (Input::GetInstance().KeyPress(VK_LBUTTON))
	{
		PlayerShoot::GetInstance()->EnterState(obj);
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
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

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
		PlayerIdle::GetInstance()->EnterState(obj);
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
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	D3DXVECTOR2 mouseDir = nowScene->mouse->pos;
	D3DXVec2Normalize(&mouseDir, &mouseDir);

	obj->gun->Shoot(nowScene->mouse->GetMouseAngleToDegree(false, obj->gun->pos - Camera::GetInstance().cameraPos), 1, obj->team);
	obj->gun->gunSpr.scene = 1;
}

void PlayerShoot::UpdateState(Player* obj, float deltaTime)
{
	timer += deltaTime;

	if (timer > obj->ability.attackSpeed - 0.1f)
		obj->gun->gunSpr.Reset();

	if (timer > obj->ability.attackSpeed)
	{
		PlayerIdle::GetInstance()->EnterState(obj);
		return;
	}
}

void PlayerShoot::ExitState(Player* obj)
{
	obj->gun->gunSpr.Reset();
	timer = 0.0f;
}
