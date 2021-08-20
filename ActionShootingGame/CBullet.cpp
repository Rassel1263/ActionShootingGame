#include "Header.h"

CBullet::CBullet(D3DXVECTOR2 pos, float theta, float damage, float speed, std::wstring team)
{
	this->pos = pos;
	this->theta = theta;
	this->damage = damage;
	this->speed = speed;
}

void CBullet::Update(float deltaTime)
{
	MoveBullet(deltaTime);
}

void CBullet::Render()
{
	bulletRI.pos = pos;
	bulletSpr.Render(bulletRI);
}

void CBullet::MoveBullet(float deltaTime)
{
	pos += D3DXVECTOR2(cosf(theta), sinf(theta)) * speed * deltaTime;
}
