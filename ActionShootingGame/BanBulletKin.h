#pragma once
class BanBulletKin : public CEnemy
{
public:
	float shootTime = 2.0f;

	BanBulletKin(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void ImageSettings() override;
	virtual void EnemyAttack(float deltaTime) override;
};

