#pragma once
class CBullet : public Object
{
public:
	float theta = 0.0f;
	float damage = 0.0f;
	float speed = 0.0f;

	std::wstring team = L"";

	Sprite bulletSpr;
	RenderInfo bulletRI;

	CBullet(D3DXVECTOR2 pos, float theta, float damage, float speed, std::wstring ownerTeam);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void MoveBullet(float deltaTime);
	virtual void OnCollision(Collider& coli) override;
};

