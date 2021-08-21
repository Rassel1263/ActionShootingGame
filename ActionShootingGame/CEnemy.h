#pragma once
class CEnemy : public Unit
{
public:
	enum class EnemyDir
	{
		IDLE_LEFT,
		IDLE_RIGHT,
		IDLE_UP,

		WALK_LEFT,
		WALK_RIGHT,
		WALK_UP
	} enemyDir;

	enum class EnemyBehavior
	{
		IDLE,
		WALK
	} behavior;

	CState<CEnemy>* nowState = NULL;
	std::map<EnemyDir, Sprite> enemySprites;

	float playerDetectionRange = 0.0f;
	float stopRange = 0.0f;
	float restTimer = 0.0f;

	CEnemy(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	bool Move(float deltaTime);
	void SetEnemyDir();
	void SetGunPos();
	bool CheckDistanceToPlayer(float detectionRange);
	D3DXVECTOR2 GetDirectionFromPlayer();
	virtual Sprite& GetNowSprite() override;
};

