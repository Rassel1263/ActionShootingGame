#pragma once
class BulletKim : public CEnemy
{
public:
	BulletKim(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void ImageSettings() override;
};

