#pragma once
class Player : public Unit
{
public:
	enum class PlayerBehavior
	{
		IDLE,
		WALK,
		ROLL
	} behavior;

	CState<Player>* nowState = NULL;

	Player();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	virtual void ImageSettings() override;
	void SetNotHoldGunUnitDir(D3DXVECTOR2 dir);
	void SetHoldGunUnitDir(D3DXVECTOR2 dir);
	bool Move(float deltaTime);
};

