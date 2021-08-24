#pragma once
class SubMachineGun : public CGun
{
public:
	SubMachineGun(Unit* owner);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

