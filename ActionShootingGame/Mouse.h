#pragma once
class Mouse : public Object
{
public:
	Mouse();

	Sprite mouseSpr;
	RenderInfo mouseRI;

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

