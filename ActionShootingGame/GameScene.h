#pragma once

class GameScene : public Scene
{
public:
	Player* player = NULL;

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

