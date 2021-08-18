#pragma once

struct RenderInfo
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
	bool bCamera = true;

	D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	
	std::vector<const Texture*> textures;

	virtual ~Sprite();
	void LoadAll(std::wstring filePath);
	void Update(float deltaTime);
	void Render(const RenderInfo& ri);
	const Texture* GetNowScene();
};

