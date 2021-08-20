#pragma once
class HandGun : public CGun
{
public:
	HandGun(Unit* owner);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

