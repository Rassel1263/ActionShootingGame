#pragma once


class PlayerUI;
class PlayerData;
class Player : public Unit
{
public:
	enum class PlayerDir
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
		ROLL_DIR_270,

		FALL,
		DIE
	} playerDir;
	enum class PlayerBehavior
	{
		IDLE,
		WALK,
		ROLL,
		FALL,
		DIE,
	} behavior;

	D3DXVECTOR2 spawnPos = { 0, 0 };

	PlayerUI* playerUI = NULL;

	std::map<PlayerDir, Sprite> playerSprites;
	CState<Player>* nowState = NULL;

	int level = 0;
	int shield = 0;
	float exp = 0.0f;

	float ultimateTime = 0.0f;
	float ultimateCoolTime = 1.0f;

	float rollTime = 0.0f;
	float rollCoolTime = 1.0f;

	bool intro = false;
	bool god = false;

	Player(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;

	virtual void ImageSettings() override;
	virtual Sprite& GetNowSprite() override;
	D3DXVECTOR2 CheckPos(D3DXVECTOR2 moveDir);
	bool Move(float deltaTime);
	void SetNotHoldGunPlayerDir(D3DXVECTOR2 dir);
	void SetHoldGunPlayerDir(D3DXVECTOR2 dir);
	void SetEffect(int index);
	void PlusExp(float exp);
	void LevelUp();
	void Hit();
	void Ultimate(float damage);
	void SetState(CState<Player>* nextState);
	void SaveData();
};

