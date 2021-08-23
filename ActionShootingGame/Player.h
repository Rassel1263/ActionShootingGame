#pragma once


class MapManager;
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
		ROLL_DIR_270

	} playerDir;
	enum class PlayerBehavior
	{
		IDLE,
		WALK,
		ROLL
	} behavior;

	D3DXVECTOR2 spawnPos = { 0, 0 };

	std::map<PlayerDir, Sprite> playerSprites;
	CState<Player>* nowState = NULL;

	MapManager* myMap = NULL;

	int level = 0;
	float exp = 0.0f;

	Player(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	virtual void ImageSettings() override;
	virtual Sprite& GetNowSprite() override;
	D3DXVECTOR2 CheckPos(D3DXVECTOR2 moveDir);
	void SpawnEnemy();
	void SetNotHoldGunPlayerDir(D3DXVECTOR2 dir);
	void SetHoldGunPlayerDir(D3DXVECTOR2 dir);
	void PlusExp(float exp);
	void CheckExp();
	bool Move(float deltaTime);
	void SetState(CState<Player>* nextState);
};

