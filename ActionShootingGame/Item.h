#pragma once
class Item : public Object
{
public:
	Sprite itemSpr;
	RenderInfo itemRI;

	Item(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

