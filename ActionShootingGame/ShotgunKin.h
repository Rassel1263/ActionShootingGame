#pragma once
class ShotgunKin : public CEnemy
{
public:
	enum class ShotgunKinType
	{
		RED,
		BLUE
	} type;

	ShotgunKin(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;;
	virtual void Render() override;
	virtual void ImageSettings() override;
};

