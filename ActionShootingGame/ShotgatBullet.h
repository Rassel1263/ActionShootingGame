#pragma once
class ShotgatBullet : public CBullet
{
public:
	ShotgatBullet(D3DXVECTOR2 pos, float theta, float damage, float speed);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli);
};

