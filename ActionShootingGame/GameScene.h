#pragma once

class GameScene : public Scene
{
public:
	bool tutorial = true;
	float tutorialTimer = 0.0f;


	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

