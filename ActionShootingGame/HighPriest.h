#pragma once
class HighPriest : public CBoss
{
public:
	HighPriest(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	void ImageSettings();
	void CreateBullet(D3DXVECTOR2 offset, int bulletCnt, float startAngle, float angle, float speed, BulletType bulletType);
	virtual bool Pattern1(float deltaTime) override;
	virtual bool Pattern2(float deltaTime) override;
	virtual bool Pattern3(float deltaTime) override;
	virtual void SetPattern(int index) override;
	virtual void SetBossImage() override;
};

