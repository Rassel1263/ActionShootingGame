#pragma once
class CBoss : public Object
{
public:
	enum class BossImage
	{
		INTRO
	};

	CBoss();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

