#pragma once

class Unit : public Object
{
public:
	enum class DIR
	{
		IDLE_DIR_0,
		IDLE_DIR_45,
		IDLE_DIR_90,
		IDLE_DIR_270,

		MOVE_DIR_0,
		MOVE_DIR_45,
		MOVE_DIR_90,
		MOVE_DIR_270,

		ROLL_DIR_0,
		ROLL_DIR_45,
		ROLL_DIR_90,
		ROLL_DIR_270
	} unitDir;

	D3DXVECTOR2 moveDir = { 0, 0 };

	std::map<DIR, Sprite> sprites;
	RenderInfo renderInfo;

	Unit(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void ImageSettings() = 0;
	Sprite& GetNowSprite();
};

