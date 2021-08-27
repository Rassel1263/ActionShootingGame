#pragma once
class MiniUnit : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	Unit* unit = NULL;

	MiniUnit(Unit* unit, Unit::UnitName unitName);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

