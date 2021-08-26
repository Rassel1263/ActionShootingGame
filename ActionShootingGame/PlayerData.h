#pragma once

struct PData
{
	Unit::UnitAblity ability;
	float ultimateCoolTime = 0.0f;
	float level = 0, exp = 0, shield = 0;
	float bullcnt = 0;
	BulletType bulletType;
	std::vector<Sprite> abilitySpr;
};

class PlayerData : public Singleton<PlayerData>
{
private:
	PData data = {};

public:
	void SaveData(PData data);
	PData LoadData();
};

