#include "Header.h"

CBoss::CBoss(D3DXVECTOR2 pos) : Unit(pos)
{
	bossImage = BossImage::IDLE_DIR_0;
	behavior = BossBehavior::IDLE;

	shadow.LoadAll(L"Assets/Sprites/Unit/Boss/shadow.png");
	nowScene->obm.AddObject(new BossUI(this));
}

void CBoss::Update(float deltaTime)
{
	if (nowState)
		nowState->UpdateState(this, deltaTime);

	GetNowSprite().Update(deltaTime);
	Unit::Update(deltaTime);
}

void CBoss::Render()
{
	renderInfo.pos = pos;
	shadow.Render(RenderInfo{ D3DXVECTOR2(pos.x, pos.y + 25) });
	GetNowSprite().Render(renderInfo);

	Unit::Render();
}

void CBoss::OnCollision(Collider& coli)
{
	if (coli.tag == L"allyBullet")
	{
		ability.hp--;
	}
}

Sprite& CBoss::GetNowSprite()
{
	return bossSprites.at(bossImage);
}

void CBoss::Die()
{
	nowScene->AddScore(1000);
	nowScene->obm.AddObject(new CEffect(L"Boom", pos + D3DXVECTOR2(0, 50), 0.05f, D3DXVECTOR2(2, 2)));
	nowScene->obm.AddObject(new Elevator(nowScene->player->spawnPos, false));
	nowScene->bossZoom = false;
	nowScene->stageClear = true;

	destroy = true;
}

bool CBoss::Move(float deltaTime)
{
	if (!CheckDistanceToPlayer(stopRange))
	{
		pos += GetDirectionFromPlayer() * ability.speed * deltaTime;
		return true;
	}

	return false;
}

void CBoss::SetState(CState<CBoss>* nextState)
{
	if (nowState)
		nowState->ExitState(this);

	nowState = nextState;
	nowState->EnterState(this);
}

void CBoss::SetBossImage()
{
	D3DXVECTOR2 dir = GetDirectionFromPlayer();

	if (behavior == BossBehavior::IDLE)
	{
		if (abs(dir.x) > 0.4)
		{
			if (dir.y > 0.4) bossImage = BossImage::IDLE_DIR_45;
			else if (dir.y < -0.4) bossImage = BossImage::IDLE_DIR_315;
			else bossImage = BossImage::IDLE_DIR_0;

			(dir.x > 0) ? renderInfo.scale.x = 1 : renderInfo.scale.x = -1;
		}
		else if (abs(dir.x <= 0.4))
			(dir.y > 0) ? bossImage = BossImage::IDLE_DIR_90 : bossImage = BossImage::IDLE_DIR_270;
	}

	if (behavior == BossBehavior::WALK)
	{
		if (abs(dir.x) > 0.4)
		{
			if (dir.y > 0.4) bossImage = BossImage::WALK_DIR_45;
			else if (dir.y < -0.4) bossImage = BossImage::WALK_DIR_315;
			else bossImage = BossImage::WALK_DIR_0;

			(dir.x > 0) ? renderInfo.scale.x = 1 : renderInfo.scale.x = -1;
		}
		else if (abs(dir.x <= 0.4))
			(dir.y > 0) ? bossImage = BossImage::WALK_DIR_90 : bossImage = BossImage::WALK_DIR_270;
	}

	if (behavior == BossBehavior::ATTACK)
		bossImage = BossImage::ATTACK;

	if (behavior == BossBehavior::DIE)
		bossImage = BossImage::DIE;
}

