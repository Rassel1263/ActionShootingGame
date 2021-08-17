#pragma once

struct RenderInfo
{
	D3DXVECTOR3 pos = { 0, 0, 0 };
	D3DXVECTOR3 scale = { 1, 1, 1 };
	D3DXVECTOR3 pivot = { 0.5, 0.5 ,0.5 };
	D3DXVECTOR3 rotate = { 0, 0, 0 };
};

struct SpriteInfo
{
	D3DXVECTOR2 pos = { 0, 0 };
	D3DXVECTOR2 scale = { 1, 1 };
	D3DXVECTOR2 pivot = { 0.5, 0.5 };
	float rotate = 0.0f;
};

class Sprite
{
public:
	int scene = 0;
	int szScene = 0;

	float aniTime = 0.0f;
	float aniMaxTime = 0.01f;

	bool bAnimation = true;
	bool bAniLoop = true;
	bool billboard = false;

	// 21Ка 12УЪ
};

