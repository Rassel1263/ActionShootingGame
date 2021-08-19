#pragma once
class CBullet : public Object
{
public:
	D3DXVECTOR2 dir = { 0, 0 };

	float damage = 0.0f;
	float speed = 0.0f;

	Sprite bulletSpr;
	RenderInfo bulletRI;

	CBullet(D3DXVECTOR2 pos, D3DXVECTOR2 dir, float damage, float speed, std::wstring ownerTeam);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

