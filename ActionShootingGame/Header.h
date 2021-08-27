#pragma once

#define SAFE_RELEASE(p) { if (p) { p->Release(); p = NULL; }}
#define SAFE_DELETE(p) { if (p) { delete p; p = NULL; }}

#define IntEnum(p) static_cast<int>(p)
#define PlusEnum(a, b, c) static_cast<a>(IntEnum(b) + IntEnum(c))

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <filesystem>
#include <functional>
#include <random>

typedef std::vector<std::vector<std::string>> StringGroupGroup;

struct MapGroup
{
	StringGroupGroup mapGroup;
	std::wstring mapName;
	int xSize;
	int ySize;
};

#include "Singleton.h"

#include "Texture.h"
#include "Sprite.h"

#include "Input.h"

#include "Camera.h"

#include "Collider.h"
#include "Object.h"

#include "ShaderManager.h"
#include "ColorShader.h"
#include "GlowShader.h"
#include "FileManager.h"

#include "CState.h"

#include "TestPixel.h"
#include "CGun.h"
#include "HandGun.h"
#include "ShotGun.h"
#include "SubMachineGun.h"

#include "CBullet.h"
#include "BasicBullet.h"
#include "PoisonBullet.h"
#include "PenetrationBullet.h"
#include "ShotgatBullet.h"

#include "Unit.h"
#include "Player.h"
#include "PlayerState.h"

#include "CEnemy.h"
#include "BulletKim.h"
#include "BanBulletKin.h"
#include "ShotgunKin.h"
#include "Shotgat.h"
#include "EnemyState.h"
#include "EnemyManager.h"
#include "Dog.h"

#include "PlayerData.h"
#include "MiniUnit.h"

#include "CBoss.h"
#include "GatlingGull.h"
#include "Gorgun.h"
#include "HighPriest.h"
#include "BossState.h"

#include "CEffect.h"
#include "Elevator.h"
#include "TutorialScroll.h"

#include "LevelUpEvent.h"
#include "Card.h"

#include "PlayerUI.h"
#include "BossUI.h"
#include "Fade.h"
#include "Font.h"
#include "Ranking.h"
#include "Minimap.h"

#include "GameOver.h"
#include "CalcPage.h"
#include "RankingPage.h"
#include "HelpPage.h"

#include "Item.h"

#include "MapToolMouse.h"
#include "MapManager.h"
#include "MapToolBlock.h"

#include "Main.h"

#include "Mouse.h"

#include "Scene.h"
extern Scene* nowScene;
#include "MapToolScene.h"
#include "MainScene.h"
#include "GameScene.h"
#include "GameScene2.h"
#include "GameScene3.h"
#include "RankingScene.h"

#include "Game.h"