#pragma once
class CEffect : public Object
{
public:
	std::function<void()>func = NULL;

	Sprite effectSpr;
	RenderInfo effectRI;

	CEffect(std::wstring filePath, D3DXVECTOR2 pos, D3DXVECTOR2 scale = {1, 1}, void(*Func)() = NULL);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

