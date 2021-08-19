#include "Header.h"

CBullet::CBullet(D3DXVECTOR2 pos, D3DXVECTOR2 dir, float damage, float speed, std::wstring team)
{
	this->pos = pos;
	this->dir = dir;
	this->damage = damage;
	this->speed = speed;
	
}

void CBullet::Update(float deltaTime)
{
}

void CBullet::Render()
{
	bulletSpr.Render(bulletRI);
}
