#include "Header.h"

GlowShader::GlowShader()
{
    shader = ShaderManager::GetInstance().GetEffect("Glow");
}

GlowShader::~GlowShader()
{
    shader = NULL;
}

HRESULT GlowShader::Prepare()
{
    return shader->SetTechnique(shader->GetTechniqueByName("Outline"));
}

HRESULT GlowShader::Begin()
{
    if (FAILED(shader->Begin(NULL, 0)))
        return E_FAIL;

    return shader->BeginPass(0);
}

HRESULT GlowShader::End()
{
    return shader->End();
}

HRESULT GlowShader::SetTexture(const Texture* texture)
{
    if (FAILED(shader->SetTexture(shader->GetParameterByName(0, "SpriteTexture"), texture->src)))
        return E_FAIL;

    float textureSize[2] = { texture->info.Width, texture->info.Height };
    return shader->SetFloatArray(shader->GetParameterByName(0, "xTextureSize"), textureSize, 2);
}

HRESULT GlowShader::SetGlowValue(float value)
{
    return shader->SetFloat(shader->GetParameterByName(0, "xGlowValue"), value);
}

void GlowShader::Render(GlowShader* shaderManager, Sprite& sprite, RenderInfo& ri)
{
    shaderManager->Prepare();
    shaderManager->SetTexture(sprite.GetNowScene());
    shaderManager->Begin();
    sprite.Render(ri);
    shaderManager->End();
}