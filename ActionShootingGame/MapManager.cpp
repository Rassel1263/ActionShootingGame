#include "Header.h"
#include "MapManager.h"

MapManager::MapManager(const std::wstring map1, const std::wstring map2)
{
	bck_1_Group = FileManager::GetInstance().ReadFile(L"Assets/MapData/" + map1 + L".dat");
	bck_2_Group = FileManager::GetInstance().ReadFile(L"Assets/MapData/" + map2 + L".dat");

	sprites.resize(9);

	sprites.at(0).LoadAll(L"Assets/Sprites/Tile/00.png");
	sprites.at(1).LoadAll(L"Assets/Sprites/Tile/01.png");
	sprites.at(2).LoadAll(L"Assets/Sprites/Tile/02.png");
	sprites.at(3).LoadAll(L"Assets/Sprites/Tile/03.png");
	sprites.at(4).LoadAll(L"Assets/Sprites/Tile/04.png");
	sprites.at(5).LoadAll(L"Assets/Sprites/Tile/05.png");
	sprites.at(6).LoadAll(L"Assets/Sprites/Tile/06.png");
	sprites.at(7).LoadAll(L"Assets/Sprites/Tile/07.png");
	sprites.at(8).LoadAll(L"Assets/Sprites/Tile/08.png");
}

void MapManager::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown(VK_SPACE))
	{
		FileManager::GetInstance().WriteFile(bck_1_Group,  bck_1_Group.mapName );
		FileManager::GetInstance().WriteFile(bck_2_Group,  bck_2_Group.mapName );
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

			if (mapString == "00")
				continue;

			rotateNum = *(bck_2_Group.mapGroup[y][x].end() - 1);

			RenderInfo tempInfo = RenderInfo{ D3DXVECTOR2(x * 18, y * 18), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), std::stof(rotateNum) * 90 };

			BlockCheck(mapString, tempInfo);

		}
	}
}

void MapManager::BlockCheck(std::string mapString, RenderInfo ri)
{
	if (mapString == "00")
		sprites.at(0).Render(ri);
	else if (mapString == "01")
		sprites.at(1).Render(ri);
	else if (mapString == "02")
		sprites.at(2).Render(ri);
	else if (mapString == "03")
		sprites.at(3).Render(ri);
	else if (mapString == "04")
		sprites.at(4).Render(ri);
	else if (mapString == "05")
		sprites.at(5).Render(ri);
	else if (mapString == "06")
		sprites.at(6).Render(ri);
	else if (mapString == "07")
		sprites.at(7).Render(ri);
	else if (mapString == "08")
		sprites.at(8).Render(ri);
}
