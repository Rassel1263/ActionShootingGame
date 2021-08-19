#pragma once

class MapToolBlock : public Object
{
public:
	Sprite spr;
	std::wstring mapNum = L"";
	MapToolBlock(const std::wstring& filePath, D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

