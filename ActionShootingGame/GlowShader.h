#pragma once

class GlowShader
{
private:
    LPD3DXEFFECT shader;
public:
    GlowShader();
    virtual ~GlowShader();

public:
    HRESULT Prepare();
    HRESULT Begin();
    HRESULT End();

    HRESULT SetTexture(const Texture* texture);
    HRESULT SetGlowValue(float value);

    void Render(GlowShader* shaderManager, Sprite& sprite, RenderInfo& ri);
};