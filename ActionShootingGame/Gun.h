#pragma once

class Unit;
class Gun : public Object
{
public:
	Unit* owner = NULL;

	Sprite gunSpr;
	RenderInfo gunRI;

	Gun(Unit* owner);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void Shoot();
};

