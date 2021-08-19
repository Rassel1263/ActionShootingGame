#include "Header.h"

MapToolMouse::MapToolMouse()
{
	Collider::AABB aabb;
	aabb.min = { -1, -1 };
	aabb.max = { 1, 1 };
	bodies.push_back(Collider(this, L"MapToolMouse", &aabb));

	spr.LoadAll(L"Assets/Sprites/tile/00.png");
	spr.bCamera = false;

	layer = 1000;
}

void MapToolMouse::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown(VK_F1))
	{
		mapNum = 1;
	}

	if (Input::GetInstance().KeyDown(VK_F2))
	{
		mapNum = 2;
	}

	for (char c = '1'; c < '6'; ++c)
		if (Input::GetInstance().KeyDown(c))
		{
			mapBlockNum = L"0" + std::to_wstring(c - '1');
			spr.LoadAll(L"Assets/Sprites/tile/" + mapBlockNum + L".png");
			rotateNum = 0;

		}

	if (Input::GetInstance().KeyDown('Q'))
	{
		rotateNum--;

		if (rotateNum < 0)
			rotateNum = 3;
	}

	if (Input::GetInstance().KeyDown('E'))
	{
		rotateNum++;

		if (rotateNum > 3)
			rotateNum = 0;
	}


	PutBlock(deltaTime);

	pos.x = Input::GetInstance().mousePos.x / 4 - Game::GetInstance().screenWidth / 8;
	pos.y = -Input::GetInstance().mousePos.y / 4 + Game::GetInstance().screenHeight / 8;

	CameraMove(deltaTime);
}

void MapToolMouse::Render()
{
	spr.Render(RenderInfo{ pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), (float)rotateNum * 90 });

	Object::Render();
}

void MapToolMouse::OnCollision(Collider& coll)
{
	if (coll.tag == L"block")
	{
		MapToolBlock* block = static_cast<MapToolBlock*>(coll.obj);
		if (Input::GetInstance().KeyDown(VK_LBUTTON))
		{
			rotateNum = 0;
			mapBlockNum = block->mapNum;
			spr = block->spr;

			inputCollision = true;
			inputTimer = 0.2f;
		}
	}
}

void MapToolMouse::PutBlock(float deltaTime)
{
	int x = (pos.x + 9 + Camera::GetInstance().cameraPos.x) / 18;
	int y = (pos.y + 9 + Camera::GetInstance().cameraPos.y) / 18;

	if (x < 0 || y < 0)
		return;

	if (x >= nowScene->mapManager->bck_1_Group.xSize || y >= nowScene->mapManager->bck_1_Group.ySize)
		return;


	if (inputTimer < 0.0)
		inputCollision = false;
	else
		inputTimer -= deltaTime;



	if (!inputCollision)
	{
		if (Input::GetInstance().KeyPress(VK_LBUTTON))
		{
			std::string tempString;
			tempString.assign(mapBlockNum.begin(), mapBlockNum.end());
			tempString += std::to_string(rotateNum);

			if  (mapNum == 1)
				nowScene->mapManager->bck_1_Group.mapGroup[y][x] = tempString;
			else if (mapNum == 2)
				nowScene->mapManager->bck_2_Group.mapGroup[y][x] = tempString;
		}

		if (Input::GetInstance().KeyPress(VK_RBUTTON))
		{
			if (mapNum == 1)
				nowScene->mapManager->bck_1_Group.mapGroup[y][x] = "00";
			else if (mapNum == 2)
				nowScene->mapManager->bck_2_Group.mapGroup[y][x] = "00";
		}

	}
	
}

void MapToolMouse::CameraMove(float deltaTime)
{
	if (Input::GetInstance().KeyPress('A'))
		Camera::GetInstance().destCameraPos.x -= cameraSpeed * deltaTime;

	if (Input::GetInstance().KeyPress('D'))
		Camera::GetInstance().destCameraPos.x += cameraSpeed * deltaTime;

	if (Input::GetInstance().KeyPress('W'))
		Camera::GetInstance().destCameraPos.y += cameraSpeed * deltaTime;

	if (Input::GetInstance().KeyPress('S'))
		Camera::GetInstance().destCameraPos.y -= cameraSpeed * deltaTime;
}
