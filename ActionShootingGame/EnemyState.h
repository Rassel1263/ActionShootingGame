#pragma once
class EnemyIdle : public CState<CEnemy>
{
public:
	static EnemyIdle* GetInstance();

	virtual void EnterState(CEnemy* obj) override;
	virtual void UpdateState(CEnemy* obj, float deltaTime) override;
	virtual void ExitState(CEnemy* obj) override;
};

class EnemyWalk : public CState<CEnemy>
{
public:
	static EnemyWalk* GetInstance();

	virtual void EnterState(CEnemy* obj) override;
	virtual void UpdateState(CEnemy* obj, float deltaTime) override;
	virtual void ExitState(CEnemy* obj) override;
};

class EnemyHit : public CState<CEnemy>
{
public:
	float rigidityTime = 0.1f;

	static EnemyHit* GetInstance();

	virtual void EnterState(CEnemy* obj) override;
	virtual void UpdateState(CEnemy* obj, float deltaTime) override;
	virtual void ExitState(CEnemy* obj) override;
};
