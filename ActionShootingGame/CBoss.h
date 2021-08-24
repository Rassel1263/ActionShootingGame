#pragma once
class CBoss : public Unit
{
public:
	enum class BossImage
	{
		INTRO,

		IDLE_DIR_0,
		IDLE_DIR_45,
		IDLE_DIR_90,
		IDLE_DIR_270,
		IDLE_DIR_315,

		WALK_DIR_0,
		WALK_DIR_45,
		WALK_DIR_90,
		WALK_DIR_270,
		WALK_DIR_315,

		ATTACK,
		DIE,
	} bossImage;

	enum class BossBehavior
	{
		IDLE,
		WALK,
		ATTACK,
		DIE
	} behavior;

	float stopRange = 100.0f;
	float restTime = 1.0f;
	float patternTime = 0.0f;
	float shootInterval = 0.0f;

	CState<CBoss>* nowState = NULL;
	std::map<BossImage, Sprite> bossSprites;
	RenderInfo bossRI;

	CBoss(D3DXVECTOR2 pos);
	virtual ~CBoss() {};

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual Sprite& GetNowSprite();

	virtual void Die();
	virtual bool Pattern1(float deltaTime) = 0;
	virtual bool Pattern2(float deltaTime) = 0;
	virtual bool Pattern3(float deltaTime) = 0;
	virtual void SetPattern(int index) = 0;

	bool Move(float deltaTime);
	void SetState(CState<CBoss>* nextState);
	void SetBossImage();
};

