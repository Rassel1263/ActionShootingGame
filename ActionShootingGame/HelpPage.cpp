#include "Header.h"

HelpPage::HelpPage()
{
	spr.LoadAll(L"Assets/Sprites/Main/Help/0.png");
}

void HelpPage::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown(VK_RETURN))
	{
		destroy = true;
		static_cast<MainScene*>(nowScene)->bClick = false;
	}
}

void HelpPage::Render()
{
	spr.Render({});
}
