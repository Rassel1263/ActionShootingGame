#include "Header.h"

TextureManager::~TextureManager()
{
    for (auto texture : textures)
    {
        SAFE_RELEASE(texture.second->src);
        SAFE_DELETE(texture.second);
    }
}

const Texture* TextureManager::GetTexture(const std::wstring filePath)
{
    auto tf = textures.find(filePath);

    if (tf != textures.end())
        return tf->second;

    Texture* texture = new Texture();
    if (FAILED(D3DXCreateTextureFromFileExW(Game::GetInstance().pd3dDevice,
        filePath.c_str(),
        D3DX_DEFAULT_NONPOW2,
        D3DX_DEFAULT_NONPOW2,
        0,
        0,
        D3DFMT_A8R8G8B8,
        D3DPOOL_DEFAULT,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        &texture->info,
        NULL,
        &texture->src)))
    {
        delete texture;
        return nullptr;
    }

    return textures.insert({ filePath, texture }).first->second;
}
