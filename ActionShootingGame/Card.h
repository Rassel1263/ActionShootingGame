#pragma once

class LevelUpEvent;
class Card : public Object
{
public:
    Sprite spr;
    D3DXVECTOR2 createPos = { 0, 0 };
    std::wstring name;

    bool changeSpr = false;
    float timer = 0.0f;

    LevelUpEvent* levelUp = NULL;
    Card(LevelUpEvent* levelUpEvent, std::wstring name, D3DXVECTOR2 pos);

    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void OnCollision(Collider& coll) override;
};