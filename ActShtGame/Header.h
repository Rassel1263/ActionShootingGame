#pragma once

#define IntEnum(p) static_cast<int>(p)
#define PlusEnum(a, b, c) static_cast<a>(IntEnum(b) + IntEnum(c))

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>

#include "DXUTcamera.h"
#include "Singleton.h"

#include "Input.h"

#include "Camera.h"

#include "Texture.h"
#include "Sprite.h"

#include "Object.h"
#include "Collider.h"

#include "Unit.h"
#include "Player.h"

#include "Scene.h"
extern Scene* nowScene;
#include "GameScene.h"

#include "Game.h"
 