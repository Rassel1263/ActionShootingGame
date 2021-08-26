#pragma once
class Font : public Object
{
public:
	std::wstring filePath = L"";

	float tracking = 0.0f;
	float& num;
	RenderInfo fontRI;

	std::vector<Sprite> fontSpr;

	Font(std::wstring fontName, D3DXVECTOR2 pos, float& num, D3DXVECTOR2 scale, float tracking, int layer = 1050);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

