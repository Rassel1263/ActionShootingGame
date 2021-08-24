#include "Header.h"

CEffect::CEffect(std::wstring filePath, D3DXVECTOR2 pos, float aniTime, D3DXVECTOR2 scale, std::function<void()> func)
{
	std::wstring path = L"Assets/Sprites/Effect/" + filePath;
	effectSpr.LoadAll(path, aniTime, false);

	this->pos = pos;
	effectRI.scale = scale;
	this->func = func;

	layer = 1;
}

CEffect::CEffect(std::wstring filePath, D3DXVECTOR2 pos, float visibleTime, bool bCamera)
{
	std::wstring path = L"Assets/Sprites/Effect/" + filePath;
	effectSpr.LoadAll(path);

	this->pos = pos;
	this->visibleTime = visibleTime;
	this->maxVisibleTime = visibleTime;

	fadeEft = true;
	effectSpr.bCamera = bCamera;

	layer = 1;
}

void CEffect::Update(float deltaTime)
{
	if (!effectSpr.bAnimation)
	{
		if(func) func();

		destroy = true;
	}

	if (fadeEft)
	{
		visibleTime -= deltaTime;
		effectSpr.color.a = visibleTime / maxVisibleTime;

		if (visibleTime <= 0.0f)
			destroy = true;
	}

	effectSpr.Update(deltaTime);
}

void CEffect::Render()
{
	effectRI.pos = pos;
	effectSpr.Render(effectRI);
}

