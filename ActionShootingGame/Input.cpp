#include "Header.h"

void Input::Start()
{
    memset(m_KeyCur, 0, sizeof(m_KeyCur));
    memset(m_KeyOld, 0, sizeof(m_KeyOld));
    memset(m_KeyMap, 0, sizeof(m_KeyMap));

    SetKeyboardState(m_KeyCur);
}

int Input::Update()
{
    memcpy(m_KeyOld, m_KeyCur, sizeof(m_KeyOld));

    memset(m_KeyCur, 0, sizeof(m_KeyCur));
    memset(m_KeyMap, 0, sizeof(m_KeyMap));

    GetKeyboardState(m_KeyCur);

    for (int i = 0; i < 256; ++i)
    {
        BYTE vKey = m_KeyCur[i] & 0x80;
        m_KeyCur[i] = (vKey) ? 1 : 0;

        INT nOld = m_KeyOld[i];
        INT nCur = m_KeyCur[i];

        if (0 == nOld && 1 == nCur) m_KeyMap[i] = InputState::INPUT_DOWN;
        else if (1 == nOld && 0 == nCur) m_KeyMap[i] = InputState::INPUT_UP;
        else if (1 == nOld && 1 == nCur) m_KeyMap[i] = InputState::INPUT_PRESS;
        else m_KeyMap[i] = InputState::INPUT_NONE;
    }

    return 0;
}

bool Input::KeyDown(int nKey)
{
    return (m_KeyMap[nKey] == InputState::INPUT_DOWN);
}

bool Input::KeyUp(int nKey)
{
    return (m_KeyMap[nKey] == InputState::INPUT_UP);
}

bool Input::KeyPress(int nKey)
{
    return (m_KeyMap[nKey] == InputState::INPUT_PRESS);
}

D3DXVECTOR2 Input::GetFixedMousePos()
{
    D3DXVECTOR2 fixedPos;
    fixedPos.x = mousePos.x / 4 - Game::GetInstance().screenWidth / 8 + Camera::GetInstance().cameraPos.x;
    fixedPos.y = -mousePos.y / 4 + Game::GetInstance().screenHeight / 8 + Camera::GetInstance().cameraPos.y;

    return fixedPos;
}
