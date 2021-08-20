#pragma once
class BasicBullet : public CBullet
{
public:
	BasicBullet(D3DXVECTOR2 pos, float theta, float damage, float speed, std::wstring ownerTeam);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

