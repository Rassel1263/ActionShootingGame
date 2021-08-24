#pragma once

class BossIdle : public CState<CBoss>
{
public:
	static BossIdle* GetInstance();

	virtual void EnterState(CBoss* obj) override;
	virtual void UpdateState(CBoss* obj, float deltaTime) override;
	virtual void ExitState(CBoss* obj) override;
};

class BossWalk : public CState<CBoss>
{
public:
	static BossWalk* GetInstance();

	virtual void EnterState(CBoss* obj) override;
	virtual void UpdateState(CBoss* obj, float deltaTime) override;
	virtual void ExitState(CBoss* obj) override;
};

class BossPattern1 : public CState<CBoss>
{
public:
	static BossPattern1* GetInstance();

	virtual void EnterState(CBoss* obj) override;
	virtual void UpdateState(CBoss* obj, float deltaTime) override;
	virtual void ExitState(CBoss* obj) override;
};

class BossPattern2 : public CState<CBoss>
{
public:
	static BossPattern2* GetInstance();

	virtual void EnterState(CBoss* obj) override;
	virtual void UpdateState(CBoss* obj, float deltaTime) override;
	virtual void ExitState(CBoss* obj) override;
};

class BossPattern3 : public CState<CBoss>
{
public:
	static BossPattern3* GetInstance();

	virtual void EnterState(CBoss* obj) override;
	virtual void UpdateState(CBoss* obj, float deltaTime) override;
	virtual void ExitState(CBoss* obj) override;
};

class BossDie : public CState<CBoss>
{
public:
	float timer = 2.0f;
	static BossDie* GetInstance();

	virtual void EnterState(CBoss* obj) override;
	virtual void UpdateState(CBoss* obj, float deltaTime) override;
	virtual void ExitState(CBoss* obj) override;
};
