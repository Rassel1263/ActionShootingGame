#include "Header.h"
#include "MapManager.h"

MapManager::MapManager(const std::wstring map1, const std::wstring map2)
{
	bck_1_Group = FileManager::GetInstance().ReadFile(L"Assets/MapData/" + map1 + L".dat");
	bck_2_Group = FileManager::GetInstance().ReadFile(L"Assets/MapData/" + map2 + L".dat");

	sprites.resize(20);
	
	int size = sprites.size();
	for (int i = 0; i < size; ++i)
	{
		WCHAR temp[50];
		wsprintf(temp, L"%02d.png", i);
		sprites.at(i).LoadAll(L"Assets/Sprites/Tile/" + nowScene->curStage + temp);
	}

	if (nowScene->gameScene)
		Collocate();
	else
	{

	}
}

void MapManager::Update(float deltaTime)
{
	if (nowScene->gameScene)
	{
	
	}
	else
	{
		if (Input::GetInstance().KeyDown(VK_SPACE))
		{
			FileManager::GetInstance().WriteFile(bck_1_Group, bck_1_Group.mapName);
			FileManager::GetInstance().WriteFile(bck_2_Group, bck_2_Group.mapName);
		}
	}
}

void MapManager::Render()
{
	for (int y = 0; y < bck_1_Group.ySize; ++y)
	{
		for (int x = 0; x < bck_1_Group.xSize; ++x)
		{
			std::string mapString;
			std::string rotateNum;

			mapString.insert(mapString.end(), bck_1_Group.mapGroup[y][x].begin(), bck_1_Group.mapGroup[y][x].begin() + 2);
			rotateNum = *(bck_1_Group.mapGroup[y][x].end() - 1);

			RenderInfo tempInfo = RenderInfo{ D3DXVECTOR2(x * 18, y * 18), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), std::stof(rotateNum) * 90 };

			bck_1_Group.mapGroup[y][x] = mapString + rotateNum;

			BlockCheck(mapString, tempInfo);
		}
	}

	for (int y = 0; y < bck_2_Group.ySize; ++y)
	{
		for (int x = 0; x < bck_2_Group.xSize; ++x)
		{
			std::string mapString;
			std::string rotateNum;

			mapString.insert(mapString.end(), bck_2_Group.mapGroup[y][x].begin(), bck_2_Group.mapGroup[y][x].begin() + 2);
			rotateNum = *(bck_2_Group.mapGroup[y][x].end() - 1);

			bck_2_Group.mapGroup[y][x] = mapString + rotateNum;

			if (mapString == "00")
				continue;

			RenderInfo tempInfo = RenderInfo{ D3DXVECTOR2(x * 18, y * 18), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), std::stof(rotateNum) * 90 };

			BlockCheck(mapString, tempInfo);

		}
	}
}

void MapManager::BlockCheck(std::string mapString, RenderInfo ri)
{
	if (nowScene->gameScene)
		if (mapString == "14" || mapString == "16" || mapString == "17" || mapString == "18" || mapString == "19")
			return;

	sprites.at(std::stoi(mapString)).Render(ri);
}

void MapManager::Collocate()
{
	for (int y = 0; y < bck_2_Group.ySize; ++y)
	{
		for (int x = 0; x < bck_2_Group.xSize; ++x)
		{
			std::string mapString;
			std::string rotateNum;

			mapString.insert(mapString.end(), bck_2_Group.mapGroup[y][x].begin(), bck_2_Group.mapGroup[y][x].begin() + 2);

			if (mapString == "00")
				continue;

			if (mapString == "14")
				nowScene->obm.AddObject(nowScene->player = new Player(D3DXVECTOR2(x * 18, y * 18)));

			if (mapString == "16")
				nowScene->obm.AddObject(new EnemyManager(D3DXVECTOR2(x * 18, y * 18), EnemyName::BULLET_KIM, 7.0f));

			if (mapString == "17")
				nowScene->obm.AddObject(new EnemyManager(D3DXVECTOR2(x * 18, y * 18), EnemyName::SHOTGUN_KIN, 9.0f));

			if (mapString == "18")
				nowScene->obm.AddObject(new EnemyManager(D3DXVECTOR2(x * 18, y * 18), EnemyName::BANBULLET_KIN, 11.0f));

			if (mapString == "19")
				nowScene->obm.AddObject(new EnemyManager(D3DXVECTOR2(x * 18, y * 18), EnemyName::SHOTGAT, 5.0f));
		}
	}
}

void MapManager::ChangeMap(const std::wstring map1, const std::wstring map2)
{
	bck_1_Group = FileManager::GetInstance().ReadFile(L"Assets/MapData/" + map1 + L".dat");
	bck_2_Group = FileManager::GetInstance().ReadFile(L"Assets/MapData/" + map2 + L".dat");

	Collocate();
}
