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

#include "FileManager.h"

#include "CState.h"

#include "TestPixel.h"
#include "CGun.h"
#include "HandGun.h"
#include "ShotGun.h"

#include "CBullet.h"
#include "BasicBullet.h"

#include "Unit.h"
#include "Player.h"
#include "PlayerState.h"

#include "CEnemy.h"
#include "BulletKim.h"
#include "ShotgunKin.h"
#include "EnemyState.h"
#include "EnemyManager.h"

#include "CEffect.h"
#include "Elevator.h"
#include "TutorialScroll.h"

#include "PlayerUI.h"
#include "Fade.h"

#include "MapToolMouse.h"
#include "MapManager.h"
#include "MapToolBlock.h"

#include "Mouse.h"

#include "Scene.h"
extern Scene* nowScene;
#include "GameScene.h"
#include "MapToolScene.h"


#include "Game.h"