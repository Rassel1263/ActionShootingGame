#include "Header.h"

Font::Font(std::wstring fontName, D3DXVECTOR2 pos, float& num, D3DXVECTOR2 scale, float tracking, int layer) 
	: num(num)
{
	this->num = num;
	filePath = L"Assets/Sprites/UI/Font/" + fontName;

	this->pos = pos;
	fontRI.scale = scale;
	this->tracking = tracking;

	std::wstring strNum = std::to_wstring((int)num);
	int fontSize = strNum.size();
	fontSpr.resize(fontSize);

	for (int i = 0; i < fontSize; ++i)
	{
		fontSpr.at(i).LoadAll(filePath + L"/" + strNum.substr(i, 1) + L".png");
		fontSpr.at(i).bCamera = false;
	}

	this->layer = layer;
}

void Font::Update(float deltaTime)
{
	std::wstring strNum = std::to_wstring((int)num);
	int fontSize = strNum.size();
	fontSpr.resize(fontSize);

	for (int i = 0; i < fontSize; ++i)
	{
		fontSpr.at(i).LoadAll(filePath + L"/" + strNum.substr(i, 1) + L".png");
		fontSpr.at(i).bCamera = false;
	}

	layer = 1050;
}

void Font::Render()
{
	int i = 0;
	for (auto& spr : fontSpr)
	{
		fontRI.pos = pos + D3DXVECTOR2(i * tracking, 0.0f);
		spr.Render(fontRI);
		i++;
	}
}
