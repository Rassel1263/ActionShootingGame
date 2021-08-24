#include "Header.h"
#include "Card.h"

Card::Card(LevelUpEvent* levelUpEvenet, std::wstring name, D3DXVECTOR2 pos)
{
    levelUp = levelUpEvenet;
    this->name = name;
    this->createPos = pos;
    spr.LoadAll(L"Assets/Sprites/UI/Card/Ani", 0.05f, false);

    Collider::AABB aabb;
    aabb.min = { -35, -58 };
    aabb.max = { 35, 58 };
    bodies.push_back(Collider(this, L"card", &aabb));

    layer = 1200;
}

void Card::Update(float deltaTime)
{
    timer += Game::GetInstance().unscaleTime;
    pos = createPos + Camera::GetInstance().cameraPos;

    if (!spr.bAnimation && !changeSpr)
    {
        changeSpr = true;
        spr.Reset();
        spr.LoadAll(L"Assets/Sprites/UI/Card/" + name + L".png");
    }

    spr.Update(Game::GetInstance().unscaleTime);
}

void Card::Render()
{
    spr.Render(RenderInfo{ pos });
    Object::Render();
}

void Card::OnCollision(Collider& coll)
{
    if (coll.tag == L"mouse")
    {
        if (timer > 0.3f)
        {
            if (Input::GetInstance().KeyDown(VK_LBUTTON))
            {
                levelUp->Effective();
                destroy = true;
            }

        }
        static_cast<Mouse*>(coll.obj)->cardName = name;
    }
}