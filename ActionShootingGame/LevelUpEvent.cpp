#include "Header.h"
#include "LevelUpEvent.h"

LevelUpEvent::LevelUpEvent()
{
    Game::GetInstance().timeScale = 0.1f;

    std::default_random_engine g(rd());
    std::shuffle(nameGroup.begin(), nameGroup.end(), g);

    Game::GetInstance().timeScale = 0.0f;

    cards.push_back(new Card(this, nameGroup[0], D3DXVECTOR2(-100, 0)));
    cards.push_back(new Card(this, nameGroup[1], D3DXVECTOR2(0, 0)));
    cards.push_back(new Card(this, nameGroup[2], D3DXVECTOR2(100, 0)));

    for (auto& card : cards)
        nowScene->obm.AddObject(card);

    spr.LoadAll(L"Assets/Sprites/UI/Card/bbck.png");
    spr.bCamera = false;
    bCamera = false;

    font.LoadAll(L"Assets/Sprites/UI/Card/Font/");
    font.bCamera = false;

    layer = 1100;
}

void LevelUpEvent::Update(float deltaTime)
{
    try
    {
        font.scene = std::stoi(nowScene->mouse->cardName);
    }
    catch (...)
    {

    }
}

void LevelUpEvent::Render()
{
    spr.Render(RenderInfo{ pos, D3DXVECTOR2(2, 2) });

    font.Render(RenderInfo{ D3DXVECTOR2(0, -100) });
}

void LevelUpEvent::Effective(int index)
{
    Game::GetInstance().timeScale = 1.0f;
    nowScene->player->SetEffect(index);
    destroy = true;

    for (auto& card : cards)
        card->destroy = true;
}