#pragma once
class CEffect : public Object
{
public:
	std::function<void()>func = NULL;
	
	bool fadeEft = false;
	float visibleTime = 0.0f;
	float maxVisibleTime = 0.0f;
	Sprite effectSpr;
	RenderInfo effectRI;

	CEffect(std::wstring filePath, D3DXVECTOR2 pos, float aniTime = 0.1f, D3DXVECTOR2 scale = {1, 1}, std::function<void()> func = NULL);
	CEffect(std::wstring filePath, D3DXVECTOR2 pos, float visibleTime, bool bCamera);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

