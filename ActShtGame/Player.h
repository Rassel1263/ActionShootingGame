#pragma once
class Player : public Unit
{
public:
	Player();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	virtual void ImageSettings() override;
	virtual bool Move(float deltaTime) override;

	void SetUnitDir(D3DXVECTOR2 dir);
};

