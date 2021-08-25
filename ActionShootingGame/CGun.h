#pragma once

class Unit;
class CGun : public Object
{
public:
	enum class BulletType
	{
		Basic,
		Poison,
	}bulletType;

	Unit* owner = NULL;

	float startAngle = 0.0f, angle = 0.0f;
	int bulletCnt = 1;

	Sprite gunSpr;
	RenderInfo gunRI;

	CGun(Unit* owner);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void Shoot(float angle, float damage, std::wstring team);
	void CreateBullet(float theta);
};

