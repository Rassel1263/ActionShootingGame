#pragma once

class Unit : public Object
{
public:
	enum class DIR
	{
		IDLE_DIR_0,
		IDLE_DIR_45,
		IDLE_DIR_90,
		IDLE_DIR_270,

		MOVE_DIR_0,
		MOVE_DIR_45,
		MOVE_DIR_90,
		MOVE_DIR_270,

		ROLL_DIR_0,
		ROLL_DIR_45,
		ROLL_DIR_90,
		ROLL_DIR_270
	} unitDir;

	struct UnitAblity
	{
		int hp = 0;
		float speed = 0.0f;
		float attackPower = 0.0f;
		float attackSpeed = 0.0f;
	} ability;

	Gun* gun = NULL;

	std::wstring team = L"";
	bool holdWeapon = false;

	D3DXVECTOR2 moveDir = { 0, 0 };

	std::map<DIR, Sprite> sprites;
	RenderInfo renderInfo;

	Sprite shadow;

	Unit(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void ImageSettings() = 0;
	void SetUnitInfo(int hp, float speed, float attackPower, float attackSpeed, std::wstring team);
	void CreateCollider(D3DXVECTOR2 min, D3DXVECTOR2 max);
	Sprite& GetNowSprite();
};

