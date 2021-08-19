#include "Header.h"
#include "Player.h"

Player::Player() : Unit(D3DXVECTOR2(0, 0))
{
	ImageSettings();
	SetUnitInfo(6, 100, 1, 0.2f, L"ally");
	CreateCollider(D3DXVECTOR2(0, -7), D3DXVECTOR2(10, 7));

	behavior = PlayerBehavior::WALK;

	PlayerIdle::GetInstance()->EnterState(this);
}

void Player::Update(float deltaTime)
{
	Camera::GetInstance().destCameraPos = pos;

	if (nowState)
		nowState->UpdateState(this, deltaTime);

	if (holdWeapon)
	{
		D3DXVECTOR2 mouseDir = nowScene->mouse->pos;
		D3DXVec2Normalize(&mouseDir, &mouseDir);
		
		SetHoldGunUnitDir(mouseDir);

		float radian = atan2(-mouseDir.y, mouseDir.x);
		float gunScale = (mouseDir.x > 0) ? 1 : -1;

		gun->gunRI.scale.y = gunScale;
		gun->gunRI.rotate = D3DXToDegree(radian);
		gun->pos = pos + D3DXVECTOR2(5 * gunScale, 7);
	}
	else
		SetNotHoldGunUnitDir(moveDir);

	if (Input::GetInstance().KeyDown('R'))
		holdWeapon = !holdWeapon;

	Unit::Update(deltaTime);
}

void Player::Render()
{
	Unit::Render();
}

void Player::ImageSettings()
{
	std::wstring filePath = L"Assets/Sprites/Unit/Player/";

	sprites[Unit::DIR::IDLE_DIR_0].LoadAll(filePath + L"Idle/0", 0.15f);
	sprites[Unit::DIR::IDLE_DIR_45].LoadAll(filePath + L"Idle/45", 0.15f);
	sprites[Unit::DIR::IDLE_DIR_90].LoadAll(filePath + L"Idle/90", 0.15f);
	sprites[Unit::DIR::IDLE_DIR_270].LoadAll(filePath + L"Idle/270", 0.15f);

	sprites[Unit::DIR::MOVE_DIR_0].LoadAll(filePath + L"Move/0", 0.15f);
	sprites[Unit::DIR::MOVE_DIR_45].LoadAll(filePath + L"Move/45", 0.15f);
	sprites[Unit::DIR::MOVE_DIR_90].LoadAll(filePath + L"Move/90", 0.15f);
	sprites[Unit::DIR::MOVE_DIR_270].LoadAll(filePath + L"Move/270", 0.15f);

	sprites[Unit::DIR::ROLL_DIR_0].LoadAll(filePath + L"Roll/0", 0.07f, false);
	sprites[Unit::DIR::ROLL_DIR_45].LoadAll(filePath + L"Roll/45", 0.07f, false);
	sprites[Unit::DIR::ROLL_DIR_90].LoadAll(filePath + L"Roll/90", 0.07f, false);
	sprites[Unit::DIR::ROLL_DIR_270].LoadAll(filePath + L"Roll/270", 0.07f, false);
}

void Player::SetNotHoldGunUnitDir(D3DXVECTOR2 dir)
{
	if (behavior == PlayerBehavior::IDLE)
		if (IntEnum(unitDir) >= 4) unitDir = Unit::DIR((int)unitDir % 4);

	if (behavior == PlayerBehavior::WALK)
	{
		if (dir.x == 0)
		{
			(dir.y > 0) ? unitDir = Unit::DIR::MOVE_DIR_90 : unitDir = Unit::DIR::MOVE_DIR_270;
		}
		else if (dir.x != 0)
		{
			(dir.y > 0) ? unitDir = Unit::DIR::MOVE_DIR_45 : unitDir = Unit::DIR::MOVE_DIR_0;
			renderInfo.scale.x = dir.x;
		}
	}

	if (behavior == PlayerBehavior::ROLL)
	{
		if (dir.x == 0)
		{
			(dir.y > 0) ? unitDir = Unit::DIR::ROLL_DIR_90 : unitDir = Unit::DIR::ROLL_DIR_270;
		}
		else if (dir.x != 0)
		{
			(dir.y > 0) ? unitDir = Unit::DIR::ROLL_DIR_45 : unitDir = Unit::DIR::ROLL_DIR_0;
			renderInfo.scale.x = dir.x;
		}
	}
}

void Player::SetHoldGunUnitDir(D3DXVECTOR2 dir)
{
	if (behavior == PlayerBehavior::IDLE)
	{
		if (abs(dir.x) > 0.4)
		{
			(dir.y > 0.3) ? unitDir = Unit::DIR::IDLE_DIR_45 : unitDir = Unit::DIR::IDLE_DIR_0;

			(dir.x > 0) ? renderInfo.scale.x = 1 : renderInfo.scale.x = -1;
		}
		else if (abs(dir.x <= 0.4))
			(dir.y > 0) ? unitDir = Unit::DIR::IDLE_DIR_90 : unitDir = Unit::DIR::IDLE_DIR_270;
	}

	if (behavior == PlayerBehavior::WALK)
	{
		if (abs(dir.x) > 0.4)
		{
			(dir.y > 0.3) ? unitDir = Unit::DIR::MOVE_DIR_45 : unitDir = Unit::DIR::MOVE_DIR_0;

			(dir.x > 0) ? renderInfo.scale.x = 1 : renderInfo.scale.x = -1;
		}
		else if (abs(dir.x <= 0.4))
			(dir.y > 0) ? unitDir = Unit::DIR::MOVE_DIR_90 : unitDir = Unit::DIR::MOVE_DIR_270;
	}
}


bool Player::Move(float deltaTime)
{
	moveDir = { 0, 0 };

	if (Input::GetInstance().KeyPress('A'))
		moveDir.x = -1;

	if (Input::GetInstance().KeyPress('D'))
		moveDir.x = 1;

	if (Input::GetInstance().KeyPress('S'))
		moveDir.y = -1;

	if (Input::GetInstance().KeyPress('W'))
		moveDir.y = 1;

	if (moveDir.x == 0 && moveDir.y == 0) return false;


	pos += moveDir * 100 * deltaTime;

	return true;
}

