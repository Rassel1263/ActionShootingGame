#pragma once

struct RenderInfo
{
	D3DXVECTOR2 pos = { 0, 0 };
	D3DXVECTOR2 scale = { 1, 1 };
	D3DXVECTOR2 pivot = { 0.5f, 0.5f };
	float rotate = 0;
};

class Sprite
{
public:
	int scene = 0;
	int szScene = 0;

	float aniMaxTime = 0.1f;
	float aniTime = 0.0f;

	bool bAniLoop = true;
	bool bAnimation = true;
	bool bCamera = true;

	float widthRatio = 1.0f;

	std::vector<const Texture*> textures;

	D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);

public:
	virtual ~Sprite();

	void LoadAll(std::wstring filePath, float aniMaxTime = 0.1f, bool bAniLoop = true);
	void Update(float deltaTime);
	void Render(const RenderInfo& ri);
	const Texture* GetNowScene();
	void Reset();
};

