#include "Header.h"

CBullet::CBullet(D3DXVECTOR2 pos, float theta, float damage, float speed, std::wstring ownerTeam)
{
	this->pos = pos;
	this->theta = theta;
	this->damage = damage;
	this->speed = speed;

	this->team = ownerTeam;
	bulletRI.rotate = D3DXToDegree(-theta);
}

void CBullet::CheckPos(D3DXVECTOR2 moveDir)
{
	D3DXVec2Normalize(&moveDir, &moveDir);

	int X = (pos.x + 10 + moveDir.x * 7 - nowScene->mapManager->pos.x) / 18;
	int Y = (pos.y + 10 + moveDir.y - nowScene->mapManager->pos.y) / 18;

	if (Y <= 0)
		pos.y += 1;

	if (X < 0 || Y < 0)
	{
		destroy = true;
		return;
	}

	if (X >= nowScene->mapManager->bck_1_Group.xSize || Y >= nowScene->mapManager->bck_1_Group.ySize)
	{
		destroy = true;
		return;
	}

	std::string upString = nowScene->mapManager->bck_2_Group.mapGroup[Y][X];
	std::string downString = nowScene->mapManager->bck_1_Group.mapGroup[Y][X];
	std::string mapString;

	mapString.insert(mapString.end(), upString.begin(), upString.begin() + 2);

	if (mapString == "03" || mapString == "04" || mapString == "05" || mapString == "06" || mapString == "07" || mapString == "09")
		Destroy();

	mapString.clear();
	mapString.insert(mapString.end(), downString.begin(), downString.begin() + 2);

	if (mapString == "03" || mapString == "04" || mapString == "05" || mapString == "06" || mapString == "07" || mapString == "09")
		Destroy();
}

void CBullet::Update(float deltaTime)
{
	layer = -pos.y + 1000;

	MoveBullet(deltaTime);

	bulletSpr.Update(deltaTime);
}

void CBullet::Render()
{
	bulletRI.pos = pos;
	bulletSpr.Render(bulletRI);

	Object::Render();
}

void CBullet::MoveBullet(float deltaTime)
{
	CheckPos(pos);
	pos += D3DXVECTOR2(cosf(theta), sinf(theta)) * speed * deltaTime;
}

void CBullet::OnCollision(Collider& coli)
{
	if ((team == L"ally" && coli.tag == L"enemy") || (team == L"enemy" && coli.tag == L"ally"))
		Destroy();
}

void CBullet::Destroy()
{
	nowScene->obm.AddObject(new CEffect(L"Bullet", pos, 0.05f));
	destroy = true;
}
