#pragma once
class Elevator : public Object
{
public:
	Sprite husks;
	Sprite floor;
	
	float timer = 2.0f;

	Elevator(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

