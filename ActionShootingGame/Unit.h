#pragma once

class Unit : public Object
{
public:
	struct UnitAblity
	{
		float hp = 0;
		float maxHp = 0;
		float speed = 0.0f;
		float attackPower = 0.0f;
		float attackSpeed = 0.0f;
	} ability;

	CGun* gun = NULL;

	std::wstring team = L"";
	bool bHit = false;
	bool bFall = false;
	float hitTimer = 0.0f;

	bool holdWeapon = false;

	bool poison = false;
	float poisonTime = 3.0f;
	float tickTime = 1.0f;

	GlowShader* glowShader = NULL;
	ColorShader* whiteShader = NULL;
	ColorShader* poisonShader = NULL;

	D3DXVECTOR2 moveDir = { 0, 0 };

	RenderInfo renderInfo;

	Sprite shadow;


	Unit(D3DXVECTOR2 pos);
	virtual ~Unit() {};

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void ImageSettings() = 0;
	virtual Sprite& GetNowSprite() = 0;
	void SetUnitInfo(float hp, float speed, float attackPower, float attackSpeed, bool holdWeapon, std::wstring team);
	void CreateCollider(D3DXVECTOR2 min, D3DXVECTOR2 max);
	float GetDistanceFromTarget(D3DXVECTOR2 targetPos);

	bool CheckDistanceToPlayer(float detectionRange);
	D3DXVECTOR2 GetDirectionFromPlayer();
};

