#include "Header.h"

CEffect::CEffect(std::wstring filePath, D3DXVECTOR2 pos, D3DXVECTOR2 scale, void (*Func)())
{
	std::wstring path = L"Assets/Sprites/Effect/" + filePath;
	effectSpr.LoadAll(path, 0.1f, false);

	this->pos = pos;
	effectRI.scale = scale;
	func = Func;
}

void CEffect::Update(float deltaTime)
{
	if (!effectSpr.bAnimation)
	{
		func();

		destroy = true;
	}

	effectSpr.Update(deltaTime);
}

void CEffect::Render()
{
	effectRI.pos = pos;
	effectSpr.Render(effectRI);
}

