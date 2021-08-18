#include "DXUT.h"
#include "Sprite.h"

namespace fs = std::filesystem;

Sprite::~Sprite()
{

}

void Sprite::LoadAll(std::wstring filePath)
{
    textures.clear();

    if (fs::is_directory(filePath))
    {
        for (auto file : fs::recursive_directory_iterator(filePath))
        {
            if (auto texture = TextureManager::GetInstance().GetTexture(file.path()))
                textures.push_back(texture);
        }
    }
    else
    {
        if (auto texture = TextureManager::GetInstance().GetTexture(filePath))
            textures.push_back(texture);
        else
            textures.push_back(TextureManager::GetInstance().GetTexture(L"ActShtGame.jpg"));
    }

    szScene = (int)textures.size();
}

void Sprite::Update(float deltaTime)
{
    if (!bAnimation) return;

    aniTime += deltaTime;

    if (aniTime > aniMaxTime)
    {
        aniTime = 0;

        if (scene < szScene - 1)
            scene++;
        else if (bAniLoop)
            scene = 0;
        else
            bAnimation = false;
    }
}

void Sprite::Render(const RenderInfo& ri)
{
    CUSTOMVERTEX* pVertices = nullptr;

    Game::GetInstance().pVB->Lock(0, 0, (void**)&pVertices, 0);

    pVertices[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    pVertices[0].color = color;
    pVertices[0].uv = D3DXVECTOR2(0.0f, 1.0f);

    pVertices[1].pos = D3DXVECTOR3(0.0f, GetNowScene()->info.Height, 0.0f);
    pVertices[1].color = color;
    pVertices[1].uv = D3DXVECTOR2(0.0f, 0.0f);

    pVertices[2].pos = D3DXVECTOR3(GetNowScene()->info.Width, 0.0f, 0.0f);
    pVertices[2].color = color;
    pVertices[2].uv = D3DXVECTOR2(1.0f, 1.0f);

    pVertices[3].pos = D3DXVECTOR3(GetNowScene()->info.Width, GetNowScene()->info.Height, 0.0f);
    pVertices[3].color = color;
    pVertices[3].uv = D3DXVECTOR2(1.0f, 0.0f);

    Game::GetInstance().pVB->Unlock();

    D3DXMATRIX matrix;
    D3DXVECTOR2 centerPos = { ri.pivot.x * GetNowScene()->info.Width, ri.pivot.y * GetNowScene()->info.Height };
    D3DXMatrixTransformation2D(&matrix, &centerPos, 0, &ri.scale, &centerPos, -D3DXToRadian(ri.rotate), &(ri.pos - centerPos));


    DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, (bCamera) ? &(matrix * Camera::GetInstance().matWorld) : &matrix);
    DXUTGetD3D9Device()->SetTexture(0, GetNowScene()->src);
    DXUTGetD3D9Device()->SetStreamSource(0, Game::GetInstance().pVB, 0, sizeof(CUSTOMVERTEX));
    DXUTGetD3D9Device()->SetFVF(D3DFVF_CUSTOMVERTEX);
    DXUTGetD3D9Device()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

const Texture* Sprite::GetNowScene()
{
    return textures[scene];
}
