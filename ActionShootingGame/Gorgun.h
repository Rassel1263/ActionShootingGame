#pragma once
class Gorgun : public CBoss
{
public:
	Gorgun(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	void ImageSettings();
	void CreateBullet(int bulletCnt, float startAngle, float angle, float speed, BulletType bulletType);
	virtual bool Pattern1(float deltaTime) override;
	virtual bool Pattern2(float deltaTime) override;
	virtual bool Pattern3(float deltaTime) override;
	virtual void SetPattern(int index) override;
	virtual void SetBossImage() override;
};

