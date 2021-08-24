#pragma once
class Shotgat : public CEnemy
{
public:
	Shotgat(D3DXVECTOR2 pos);
	
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

