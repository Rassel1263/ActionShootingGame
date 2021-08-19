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
#include <vector>
#include <map>
#include <fstream>
#include <filesystem>
#include <sstream>

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

#include "MapToolMouse.h"
#include "MapManager.h"
#include "MapToolBlock.h"

#include "CState.h"

#include "Gun.h"

#include "CBullet.h"

#include "Unit.h"
#include "Player.h"
#include "PlayerState.h"

#include "Mouse.h"

#include "Scene.h"
extern Scene* nowScene;
#include "GameScene.h"
#include "MapToolScene.h"


#include "Game.h"