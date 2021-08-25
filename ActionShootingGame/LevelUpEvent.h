#pragma once

class Card;
class LevelUpEvent : public Object
{
public:
    Sprite spr;
    Sprite font;

    std::vector<Card*> cards;

    float timer = 0.0f;

    std::vector<std::wstring> nameGroup = { L"00", L"01", L"02", L"03", L"04", L"05", L"06", L"07"};
    std::random_device rd;

    LevelUpEvent();

    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    void Effective(int index);
};