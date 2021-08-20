#pragma once
class Mouse : public Object
{
public:
	Mouse();

	Sprite mouseSpr;
	RenderInfo mouseRI;

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	D3DXVECTOR2 GetMouseDir();
	float GetMouseAngleToRadian( bool reverseY = false, D3DXVECTOR2 centerPos = { 0, 0 });
	float GetMouseAngleToDegree( bool reverseY = false, D3DXVECTOR2 centerPos = { 0, 0 });
};

