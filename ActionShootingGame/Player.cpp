#include "Header.h"
#include "Player.h"

Player::Player() : Unit(D3DXVECTOR2(0, 0))
{
	ImageSettings();
	SetUnitInfo(6, 100, 1, 0.2f, false, L"ally");
	CreateCollider(D3DXVECTOR2(-7, 0), D3DXVECTOR2(7, 10));

	playerDir = PlayerDir::IDLE_DIR_0;
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
		SetHoldGunPlayerDir(nowScene->mouse->GetMouseDir());
		float gunScale = (nowScene->mouse->GetMouseDir().x > 0) ? 1 : -1;

		gun->gunRI.rotate = nowScene->mouse->GetMouseAngleToDegree(true);
		gun->gunRI.scale.y = gunScale;
		gun->pos = pos + D3DXVECTOR2(5 * gunScale, 7);
	}
	else SetNotHoldGunPlayerDir(moveDir);

	if (Input::GetInstance().KeyDown('R'))
		holdWeapon = !holdWeapon;

	GetNowSprite().Update(deltaTime);
	Unit::Update(deltaTime);
}

void Player::Render()
{
	renderInfo.pos = pos;
	shadow.Render(RenderInfo{ D3DXVECTOR2(pos.x, pos.y + 1) });
	GetNowSprite().Render(renderInfo);

	Unit::Render();
}

void Player::ImageSettings()
{
	std::wstring filePath = L"Assets/Sprites/Unit/Player/";

	playerSprites[PlayerDir::IDLE_DIR_0].LoadAll(filePath + L"Idle/0", 0.15f);
	playerSprites[PlayerDir::IDLE_DIR_45].LoadAll(filePath + L"Idle/45", 0.15f);
	playerSprites[PlayerDir::IDLE_DIR_90].LoadAll(filePath + L"Idle/90", 0.15f);
	playerSprites[PlayerDir::IDLE_DIR_270].LoadAll(filePath + L"Idle/270", 0.15f);
	
	playerSprites[PlayerDir::MOVE_DIR_0].LoadAll(filePath + L"Move/0", 0.15f);
	playerSprites[PlayerDir::MOVE_DIR_45].LoadAll(filePath + L"Move/45", 0.15f);
	playerSprites[PlayerDir::MOVE_DIR_90].LoadAll(filePath + L"Move/90", 0.15f);
	playerSprites[PlayerDir::MOVE_DIR_270].LoadAll(filePath + L"Move/270", 0.15f);
	
	playerSprites[PlayerDir::ROLL_DIR_0].LoadAll(filePath + L"Roll/0", 0.07f, false);
	playerSprites[PlayerDir::ROLL_DIR_45].LoadAll(filePath + L"Roll/45", 0.07f, false);
	playerSprites[PlayerDir::ROLL_DIR_90].LoadAll(filePath + L"Roll/90", 0.07f, false);
	playerSprites[PlayerDir::ROLL_DIR_270].LoadAll(filePath + L"Roll/270", 0.07f, false);
}

Sprite& Player::GetNowSprite()
{
	return playerSprites.at(playerDir);
}

void Player::SetNotHoldGunPlayerDir(D3DXVECTOR2 dir)
{
	if (behavior == PlayerBehavior::IDLE)
		if (IntEnum(playerDir) >= 4) playerDir = PlayerDir((int)playerDir % 4);

	if (behavior == PlayerBehavior::WALK)
	{
		if (dir.x == 0)
		{
			(dir.y > 0) ? playerDir = PlayerDir::MOVE_DIR_90 : playerDir = PlayerDir::MOVE_DIR_270;
		}
		else if (dir.x != 0)
		{
			(dir.y > 0) ? playerDir = PlayerDir::MOVE_DIR_45 : playerDir = PlayerDir::MOVE_DIR_0;
			renderInfo.scale.x = dir.x;
		}
	}

	if (behavior == PlayerBehavior::ROLL)
	{
		if (dir.x == 0)
		{
			(dir.y > 0) ? playerDir = PlayerDir::ROLL_DIR_90 : playerDir = PlayerDir::ROLL_DIR_270;
		}
		else if (dir.x != 0)
		{
			(dir.y > 0) ? playerDir = PlayerDir::ROLL_DIR_45 : playerDir = PlayerDir::ROLL_DIR_0;
			renderInfo.scale.x = dir.x;
		}
	}
}

void Player::SetHoldGunPlayerDir(D3DXVECTOR2 dir)
{
	if (behavior == PlayerBehavior::IDLE)
	{
		if (abs(dir.x) > 0.4)
		{
			(dir.y > 0.3) ? playerDir = PlayerDir::IDLE_DIR_45 : playerDir = PlayerDir::IDLE_DIR_0;

			(dir.x > 0) ? renderInfo.scale.x = 1 : renderInfo.scale.x = -1;
		}
		else if (abs(dir.x <= 0.4))
			(dir.y > 0) ? playerDir = PlayerDir::IDLE_DIR_90 : playerDir = PlayerDir::IDLE_DIR_270;
	}

	if (behavior == PlayerBehavior::WALK)
	{
		if (abs(dir.x) > 0.4)
		{
			(dir.y > 0.3) ? playerDir = PlayerDir::MOVE_DIR_45 : playerDir = PlayerDir::MOVE_DIR_0;

			(dir.x > 0) ? renderInfo.scale.x = 1 : renderInfo.scale.x = -1;
		}
		else if (abs(dir.x <= 0.4))
			(dir.y > 0) ? playerDir = PlayerDir::MOVE_DIR_90 : playerDir = PlayerDir::MOVE_DIR_270;
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

