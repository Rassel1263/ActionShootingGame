#include "Header.h"
#include "ShaderManager.h"

ShaderManager::~ShaderManager()
{
    for (auto& effect : effects)
    {
        SAFE_RELEASE(effect.second);
    }
}

HRESULT ShaderManager::CreateEffect(std::string name, LPCWSTR filename, DWORD flag)
{
#ifdef _DEBUG
    flag != D3DXSHADER_DEBUG;
#endif // _DEBUG

    LPD3DXBUFFER pError;
    LPD3DXEFFECT pEffect;

    if (SUCCEEDED(D3DXCreateEffectFromFileW(Game::GetInstance().pd3dDevice, filename, NULL, NULL, flag,
        NULL, &pEffect, &pError)))
    {
        auto founded = effects.find(name);

        if (founded != effects.end())
        {
            if (founded->second)
            {
                SAFE_RELEASE(founded->second);
            }
            effects.erase(name);
        }
        effects.insert(std::make_pair(name, pEffect));

        return S_OK;
    }
    else
    {
        if (pError)
        {
            std::cout << (char*)pError->GetBufferPointer() << std::endl;
            pError->Release();

            return E_FAIL;
        }
    }

    return E_NOTIMPL;
}

LPD3DXEFFECT& ShaderManager::GetEffect(std::string name)
{
    return effects[name];
    // TODO: 여기에 return 문을 삽입합니다.
}