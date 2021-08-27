#include "Header.h"

CBoss::CBoss(D3DXVECTOR2 pos, UnitName unitName) : Unit(pos, unitName)
{
	bossImage = BossImage::IDLE_DIR_0;
	behavior = BossBehavior::IDLE;

	hitTimer = 0.1f;

	shadow.LoadAll(L"Assets/Sprites/Unit/Boss/shadow.png");
	nowScene->obm.AddObject(new BossUI(this));

	whiteShader = new ColorShader();
	poisonShader = new ColorShader();
}

void CBoss::Update(float deltaTime)
{
	layer = -pos.y + 1000;

	if (poison)
	{
		poisonTime -= deltaTime;
		tickTime -= deltaTime;

		if (tickTime <= 0.0f)
		{
			ability.hp -= 1;
			bHit = true;
			tickTime = 1.0f;
		}

		if (poisonTime <= 0.0f)
		{
			poisonTime = 2.0f;
			poison = false;
		}
	}

	if (bHit)
	{
		hitTimer -= deltaTime;

		if (hitTimer <= 0.0f)
		{
			hitTimer = 0.1f;
			bHit = false;
		}
	}
	if (nowState)
		nowState->UpdateState(this, deltaTime);

	GetNowSprite().Update(deltaTime);
	Unit::Update(deltaTime);
}

void CBoss::Render()
{
	renderInfo.pos = pos;
	shadow.Render(RenderInfo{ D3DXVECTOR2(pos.x, pos.y)});

	if(bHit)
		whiteShader->Render(whiteShader, GetNowSprite(), renderInfo);
	else if(poison)
		poisonShader->Render(poisonShader, GetNowSprite(), renderInfo, D3DXVECTOR4(0.25f, 0.35f, 0.2f, 0.0f));
	else
		GetNowSprite().Render(renderInfo);

	Unit::Render();
}

void CBoss::OnCollision(Collider& coli)
{
	if (coli.tag == L"allyBullet")
	{
		if (!bHit)
			 Hit(static_cast<CBullet*>(coli.obj)->damage);
	}
}

Sprite& CBoss::GetNowSprite()
{
	return bossSprites.at(bossImage);
}

void CBoss::Die()
{
	nowScene->AddScore(1000);
	nowScene->obm.AddObject(new CEffect(L"Boom", pos, 0.05f, D3DXVECTOR2(2, 2)));
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

void CBoss::Hit(float damage)
{
	bHit = true;
	ability.hp -= damage;
}

void CBoss::SetState(CState<CBoss>* nextState)
{
	if (nowState)
		nowState->ExitState(this);

	nowState = nextState;
	nowState->EnterState(this);
}
