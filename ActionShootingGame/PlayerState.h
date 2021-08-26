#pragma once

class PlayerIdle : public CState<Player>
{
public:
	static PlayerIdle* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerWalk : public CState<Player>
{
public:
	static PlayerWalk* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerDodgeRoll : public CState<Player>
{
public:
	bool holdWeapon = false;
	static PlayerDodgeRoll* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerFall : public CState<Player>
{
public:
	static PlayerFall* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerDie: public CState<Player>
{
public:
	static PlayerDie* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerShoot : public CState<Player>
{
public:
	float timer = 0.0f;

	static PlayerShoot* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};