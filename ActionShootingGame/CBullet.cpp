#include "Header.h"

CBullet::CBullet(D3DXVECTOR2 pos, float theta, float damage, float speed, std::wstring ownerTeam)
{
	this->pos = pos;
	this->theta = theta;
	this->damage = damage;
	this->speed = speed;

	this->team = ownerTeam;
}

void CBullet::Update(float deltaTime)
{
	MoveBullet(deltaTime);

	D3DXVECTOR2 centerPos = nowScene->player->spawnPos;
	if (pos.x > centerPos.x + 500 || pos.x < centerPos.x - 500 ||
		pos.y > centerPos.y + 400 || pos.y < centerPos.y - 400)
		destroy = true;
}

void CBullet::Render()
{
	bulletRI.pos = pos;
	bulletSpr.Render(bulletRI);

	Object::Render();
}

void CBullet::MoveBullet(float deltaTime)
{
	pos += D3DXVECTOR2(cosf(theta), sinf(theta)) * speed * deltaTime;
}

void CBullet::OnCollision(Collider& coli)
{
	if (coli.tag == L"allyBullet" || coli.tag == L"enemyBullet") return;
	if (coli.tag != team)
		destroy = true;
}
