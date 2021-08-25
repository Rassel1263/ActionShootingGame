#include "Header.h"

Main::Main()
{
	bg.LoadAll(L"Assets/Sprites/Main/Bg", 0.2f);

	button.resize(2);
	button[0].LoadAll(L"Assets/Sprites/Main/Button/0");
	button[1].LoadAll(L"Assets/Sprites/Main/Button/1");

	button[1].scene = 1;
}

void Main::Update(float deltaTime)
{
	int prevNum = cNum;
	
	if (Input::GetInstance().KeyDown(VK_DOWN))
		if(cNum < 1) cNum++;

	if (Input::GetInstance().KeyDown(VK_UP))
		if (cNum > 0) cNum--;

	if (Input::GetInstance().KeyDown(VK_RETURN))
	{
		if (cNum == 0)
		{
			auto func = [] {Game::GetInstance().ChangeScecne(new GameScene()); };
			nowScene->obm.AddObject(new Fade(true, 2.0f, func));
		}

		if (cNum == 1)
			PostQuitMessage(0);
	}

	if (prevNum != cNum)
	{
		button[cNum].scene = 0;
		button[prevNum].scene = 1;
	}

	bg.Update(deltaTime);
}

void Main::Render()
{
	bg.Render({});

	button[0].Render({D3DXVECTOR2(-190, -70) });
	button[1].Render({D3DXVECTOR2(-190, -100) });


}
