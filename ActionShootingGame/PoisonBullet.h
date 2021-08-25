#pragma once
class PoisonBullet : public CBullet
{
public:
	PoisonBullet(D3DXVECTOR2 pos, float theta, float damage, float speed, std::wstring ownerTeam);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli);
};

