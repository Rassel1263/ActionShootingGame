#include "DXUT.h"
#include "Player.h"

Player::Player() : Unit(D3DXVECTOR2(0, 0))
{
	ImageSettings();
}

void Player::Update(float deltaTime)
{
	Move(deltaTime);

	Unit::Update(deltaTime);
}

void Player::Render()
{
	Unit::Render();
}

void Player::ImageSettings()
{
	std::wstring filePath = L"Assets/Sprites/Unit/Player/";

	sprites[Unit::DIR::IDLE_DIR_0].LoadAll(L"Assets/Sprites/Unit/Player/Move/0");
	sprites[Unit::DIR::IDLE_DIR_45].LoadAll(filePath + L"Idle/45");
	sprites[Unit::DIR::IDLE_DIR_90].LoadAll(filePath + L"Idle/90");
	sprites[Unit::DIR::IDLE_DIR_270].LoadAll(filePath + L"Idle/270");

	sprites[Unit::DIR::MOVE_DIR_0].LoadAll(filePath + L"Move/0");
	sprites[Unit::DIR::MOVE_DIR_45].LoadAll(filePath + L"Move/45");
	sprites[Unit::DIR::MOVE_DIR_90].LoadAll(filePath + L"Move/90");
	sprites[Unit::DIR::MOVE_DIR_270].LoadAll(filePath + L"Move/270");
}

void Player::SetUnitDir(D3DXVECTOR2 dir)
{
}

bool Player::Move(float deltaTime)
{
	D3DXVECTOR2 moveDir = { 0, 0 };

	if (Input::GetInstance().KeyPress('A'))
		moveDir.x = -1;
	
	if (Input::GetInstance().KeyPress('D'))
		moveDir.x = 1;

	if (Input::GetInstance().KeyPress('S'))
		moveDir.y = -1;

	if (Input::GetInstance().KeyPress('W'))
		moveDir.y = 1;
		

	if (moveDir.x == 0 && moveDir.y == 0)
	{
		if(IntEnum(unitDir) > 4) unitDir = PlusEnum(Unit::DIR, unitDir, -4);
		return false;
	}
	else if (moveDir.x == 0)
		(moveDir.y > 0) ? unitDir = Unit::DIR::MOVE_DIR_90 : unitDir = Unit::DIR::MOVE_DIR_270;
	else if (moveDir.x != 0)
	{
		(moveDir.y > 0) ? unitDir = Unit::DIR::MOVE_DIR_45 : unitDir = Unit::DIR::MOVE_DIR_0;
		renderInfo.scale.x = moveDir.x;
	}


	pos += moveDir * 100 * deltaTime;

	return true;
}
