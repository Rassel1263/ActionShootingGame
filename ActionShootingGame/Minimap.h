#pragma once
class Minimap : public Object
{
public:
	enum class UnitType
	{
		PLAYER,
		BULLET_KIN,
		BANBULLET_KIN,
		SHOTGUNKIN_BLUE,
		SHOTGUNKIN_RED,
		SHOTGAT
	};

	Sprite border;
	std::vector<Unit*> units;

	Minimap();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void AddUnit(D3DXVECTOR2* pos, UnitType unitType);
};

