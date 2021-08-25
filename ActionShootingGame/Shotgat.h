#pragma once
class Shotgat : public CEnemy
{
public:
	Shotgat(D3DXVECTOR2 pos);
	
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void ImageSettings() override;
	virtual void EnemyAttack(float deltaTime) override;
	virtual void Die() override;
};

