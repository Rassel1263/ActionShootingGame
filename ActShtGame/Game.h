#pragma once

struct CUSTOMVERTEX
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class Game : public Singleton<Game>
{
public:
	int screenWidth = 1920;
	int screenHeight = 1080;

	float timeScale = 1.0f;
	float unscaleTime = 0.0f;

	LPDIRECT3DVERTEXBUFFER9 pVB;
	LPD3DXSPRITE pSprite;
	LPD3DXLINE pLine;

public:
	~Game();

	void Init();
	void Update(float deltaTime);
	void Render();
	void DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXMATRIX matrix, D3DCOLOR color = D3DCOLOR_ARGB(255, 0, 0, 0), float width = 2.0f);
	void Check();
	D3DXVECTOR2 ScreenSize();
};

