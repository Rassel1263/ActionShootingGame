#include "Header.h"
#include "Player.h"

Player::Player(D3DXVECTOR2 pos) : Unit(pos)
{
	this->spawnPos = pos;

	ImageSettings();
	SetUnitInfo(6, 100, 5, 0.1f, true, L"ally"); 
	level = 1;
	hitTimer = 1.5f;
	intro = true;

	Camera::GetInstance().destCameraPos = pos;

	nowScene->obm.AddObject(gun = new HandGun(this));
	nowScene->obm.AddObject(new PlayerUI(this));

	CreateCollider(D3DXVECTOR2(-7, 0), D3DXVECTOR2(7, 10));

	playerDir = PlayerDir::IDLE_DIR_0;
	behavior = PlayerBehavior::WALK;

	SetState(PlayerIdle::GetInstance());
}

void Player::Update(float deltaTime)
{
	if (intro) return;

	if (Input::GetInstance().KeyDown('Z'))
		Hit();

	if (Input::GetInstance().KeyDown('C'))
		PlusExp(10);
	
	if(Input::GetInstance().KeyDown('V'))
		nowScene->obm.AddObject(new Elevator(pos + D3DXVECTOR2(100, 0), false));

	if (!nowScene->bossZoom)
	{
		if (pos.x > spawnPos.x - 70 && pos.x < spawnPos.x + 70)
			Camera::GetInstance().destCameraPos.x = pos.x;

		if (pos.y > spawnPos.y - 170 && pos.y < spawnPos.y + 170)
			Camera::GetInstance().destCameraPos.y = pos.y;
	}

	if (nowState)
		nowState->UpdateState(this, deltaTime);

	if (holdWeapon)
	{
		SetHoldGunPlayerDir(nowScene->mouse->GetMouseDir());
		float gunScale = (nowScene->mouse->GetMouseDir().x > 0) ? 1 : -1;

		gun->gunRI.rotate = nowScene->mouse->GetMouseAngleToDegree(true, pos);
		gun->gunRI.scale.y = gunScale;
		gun->pos = pos + D3DXVECTOR2(5 * gunScale, 7);
	}
	else SetNotHoldGunPlayerDir(moveDir);

	if (bHit)
	{
		hitTimer -= deltaTime;

		if (hitTimer <= 0.0f)
		{
			hitTimer = 2.0f;
			bHit = false;
		}
	}

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

void Player::OnCollision(Collider& coli)
{
	if (coli.tag == L"enemyBullet")
	{
		if (!bHit)
		{
			Hit();
		}
	}
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

D3DXVECTOR2 Player::CheckPos(D3DXVECTOR2 moveDir)
{
	//D3DXVec2Normalize(&moveDir, &moveDir);

	int X = (pos.x + 9 + moveDir.x * 7 - nowScene->mapManager->pos.x) / 18;
	int Y = (pos.y + 9 + moveDir.y - nowScene->mapManager->pos.y) / 18;

	if (Y <= 0)
		pos.y += 1;

	if (X < 0 || Y < 0)
		return D3DXVECTOR2(0, 0);


	if (X >= nowScene->mapManager->bck_1_Group.xSize || Y >= nowScene->mapManager->bck_1_Group.ySize)
		return D3DXVECTOR2(0, 0);

	std::string upString = nowScene->mapManager->bck_2_Group.mapGroup[Y][X];
	std::string downString = nowScene->mapManager->bck_1_Group.mapGroup[Y][X];
	std::string mapString;

	mapString.insert(mapString.end(), upString.begin(), upString.begin() + 2);

	if (mapString == "03" || mapString == "04" || mapString == "05" || mapString == "06" || mapString == "07" || mapString == "08" || mapString == "09")
		return D3DXVECTOR2(0, 0);

	mapString.clear();
	mapString.insert(mapString.end(), downString.begin(), downString.begin() + 2);

	if (mapString == "03" || mapString == "04" || mapString == "05" || mapString == "06" || mapString == "07" || mapString == "08" || mapString == "09")
		return D3DXVECTOR2(0, 0);

	return moveDir;
}

void Player::SpawnEnemy()
{
	nowScene->obm.AddObject(new ShotgunKin(pos));
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

void Player::PlusExp(float exp)
{
	this->exp += exp;

	CheckExp();
}

void Player::CheckExp()
{
	if (exp >= 100)
	{
		exp = 0.0f;
		LevelUp();
	}
}

void Player::LevelUp()
{
	level++;
	auto Func = []() { nowScene->obm.AddObject(new LevelUpEvent()); };
	std::function<void()> func;
	Camera::GetInstance().cameraQuaken = { 5, 5 };
	nowScene->obm.AddObject(new CEffect(L"LevelUp/Effect", pos + D3DXVECTOR2(0, 15), 0.02f, D3DXVECTOR2(1, 1), Func));
}

void Player::Hit()
{
	nowScene->obm.AddObject(new CEffect(L"ouch.png", D3DXVECTOR2(0, 0), 0.3f, false));
	bHit = true;
	ability.hp--;
	Camera::GetInstance().cameraQuaken = { 4, 4 };
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

	moveDir = CheckPos(moveDir);
	pos += moveDir * 100 * deltaTime;

	return true;
}

void Player::SetState(CState<Player>* nextState)
{
	if (nowState)
		nowState->ExitState(this);

	nowState = nextState;
	nowState->EnterState(this);
}

