#pragma once
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

	std::map<PlayerDir, Sprite> playerSprites;
	CState<Player>* nowState = NULL;

	Player();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	virtual void ImageSettings() override;
	virtual Sprite& GetNowSprite() override;
	void SetNotHoldGunPlayerDir(D3DXVECTOR2 dir);
	void SetHoldGunPlayerDir(D3DXVECTOR2 dir);
	bool Move(float deltaTime);
};

