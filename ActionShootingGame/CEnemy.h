#pragma once
class CEnemy : public Unit
{
public:
	enum class EnemyImage
	{
		IDLE_LEFT,
		IDLE_RIGHT,
		IDLE_UP,

		WALK_LEFT,
		WALK_RIGHT,
		WALK_UP,

		HIT
	} enemyImage;

	enum class EnemyBehavior
	{
		IDLE,
		WALK,
		HIT
	} behavior;

	CState<CEnemy>* nowState = NULL;
	std::map<EnemyImage, Sprite> enemySprites;

	float playerDetectionRange = 0.0f;
	float stopRange = 0.0f;
	float restTimer = 0.0f;

	CEnemy(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual Sprite& GetNowSprite() override;
	virtual void EnemyAttack(float deltaTime);
	bool Move(float deltaTime);
	void SetEnemyImage();
	void SetGunPos();
	bool CheckDistanceToPlayer(float detectionRange);
	D3DXVECTOR2 GetDirectionFromPlayer();
};

