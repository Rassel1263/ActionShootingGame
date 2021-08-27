#pragma once
class Minimap : public Object
{
public:
	Sprite border;

	Minimap();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

