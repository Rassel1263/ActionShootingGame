#include "Header.h"

RankingPage::RankingPage()
{
	spr.LoadAll(L"Assets/Sprites/UI/Ranking2.png");

	std::wifstream read(L"Rank.txt");

	rank.resize(3);
	initial.resize(3);
	score.resize(3);

	for (int i = 0; i < 3; ++i)
		initial[i].resize(i);

	if (read.is_open())
	{
		for (int i = 0; i < 3; ++i)
		{
			read >> rank[i].score;
			read >> rank[i].initial;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		initial[i].resize(3);

		for (int j = 0; j < 3; ++j)
			initial[i][j].LoadAll(L"Assets/Sprites/UI/Font/Word/" + rank[i].initial.substr(j, 1) + L".png");

		std::wstring nums = std::to_wstring(rank[i].score);
		int numSize = nums.size();
		score[i].resize(numSize);

		for (int j = 0; j < numSize; ++j)
			score[i][j].LoadAll(L"Assets/Sprites/UI/Font/Number/" + nums.substr(j, 1) + L".png");
	}
}

void RankingPage::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown(VK_RETURN))
	{
		destroy = true;
		static_cast<MainScene*>(nowScene)->bClick = false;
	}
}

void RankingPage::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	int yCount = 0;

	for (int i = 0; i < 3; ++i)
	{
		int xCount = 0;

		for (auto& spr : initial[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(pos.x - 90 + xCount * 30, 30 - yCount * 50) });
			xCount++;
		}

		xCount = 0;
		for (auto& spr : score[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(pos.x + 70 + xCount * 20, 30 - yCount * 50), D3DXVECTOR2(2, 2) });
			xCount++;
		}

		yCount++;
	}
}
