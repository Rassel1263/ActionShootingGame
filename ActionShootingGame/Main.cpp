#include "Header.h"

Main::Main()
{
	Camera::GetInstance().destCameraPos = { 0, 0 };
	Camera::GetInstance().cameraPos = { 0, 0 };

	bg.LoadAll(L"Assets/Sprites/Main/Bg", 0.2f);

	button.resize(4);
	button[0].LoadAll(L"Assets/Sprites/Main/Button/0");
	button[1].LoadAll(L"Assets/Sprites/Main/Button/1");
	button[2].LoadAll(L"Assets/Sprites/Main/Button/2");
	button[3].LoadAll(L"Assets/Sprites/Main/Button/3");

	button[1].scene = 1;
	button[2].scene = 1;
	button[3].scene = 1;
}

void Main::Update(float deltaTime)
{
	if (static_cast<MainScene*>(nowScene)->bClick) return;

	int prevNum = cNum;
	
	if (Input::GetInstance().KeyDown(VK_DOWN))
		if(cNum < 3) cNum++;

	if (Input::GetInstance().KeyDown(VK_UP))
		if (cNum > 0) cNum--;

	if (Input::GetInstance().KeyDown(VK_RETURN))
	{
		static_cast<MainScene*>(nowScene)->bClick = true;

		if (cNum == 0)
		{
			auto func = [] {Game::GetInstance().ChangeScecne(new GameScene()); };
			nowScene->obm.AddObject(new Fade(true, 2.0f, func));
		}

		if (cNum == 1)
			nowScene->obm.AddObject(new RankingPage());
		       
		if (cNum == 2)
			nowScene->obm.AddObject(new HelpPage());

		if (cNum == 3)
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

	int cnt = 0;
	for (auto& btn : button)
	{
		btn.Render({ D3DXVECTOR2(-190, -50 + cnt * -20) });
		cnt++;
	}
}
