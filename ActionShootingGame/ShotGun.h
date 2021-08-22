#pragma once
class ShotGun : public CGun
{
public:
	ShotGun(Unit* owner);

	virtual void Update(float deltaTime);
	virtual void Render();
};

