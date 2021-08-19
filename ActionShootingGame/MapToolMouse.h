#pragma once

class MapToolMouse : public Object
{
public:
	float cameraSpeed = 50;
	float inputTimer = 0.0f;
	int  rotateNum = 0;

	bool inputCollision = false;

	int mapNum = 1;
	std::wstring mapBlockNum = L"00";
	Sprite spr;

	MapToolMouse();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coll) override;

	void PutBlock(float deltaTime);
	void CameraMove(float deltaTime);
};

