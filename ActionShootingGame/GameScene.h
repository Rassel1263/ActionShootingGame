#pragma once

class GameScene : public Scene
{
public:
	bool tutorial = false;

	float gameTime = 180.0f;

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

