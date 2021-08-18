#include "DXUT.h"
#include "TestObj.h"

TestObj::TestObj()
{
	spr.LoadAll(L"a");
	pos = { 0 ,0 };
}

void TestObj::Update(float deltaTime)
{
	if (Input::GetInstance().KeyPress(VK_LEFT))
		pos.x -= 100 * deltaTime;
}

void TestObj::Render()
{
	info.pos = pos;
	spr.Render(info);
}
