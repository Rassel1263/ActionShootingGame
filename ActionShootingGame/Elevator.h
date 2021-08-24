#pragma once
class Elevator : public Object
{
public:
	Sprite husks[2];
	Sprite floor;
	
	int renderNum = 0;
	float timer = 2.0f;
	bool stageStart = true;
	bool drawFade = false;
	bool boarding = false;

	Elevator(D3DXVECTOR2 pos, bool stageStart);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

