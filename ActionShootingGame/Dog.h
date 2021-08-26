#pragma once


class Dog : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	CEnemy* target = NULL;

	Dog(D3DXVECTOR2 pos);
	
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

