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

	bool haveGun = false;

	CState<Player>* nowState = NULL;

	Player();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	virtual void ImageSettings() override;
	void SetUnitDir(D3DXVECTOR2 dir);
	bool Move(float deltaTime);
};

