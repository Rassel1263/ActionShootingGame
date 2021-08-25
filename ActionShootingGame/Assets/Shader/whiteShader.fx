Texture2D SpriteTexture;
float4 color;

sampler2D InputSampler = sampler_state
{
    Texture = <SpriteTexture>;
};

struct ShaderOuput
{
    float2 uv : TEXCOORD0;
};

float4 main(ShaderOuput input) : COLOR
{
    float4 albedo = tex2D(InputSampler, input.uv);
    
    return float4(albedo.rgb + color.rgb, albedo.a);
}

technique Outline
{
    pass pass0
    {
        AlphaBlendEnable = TRUE;

        PixelShader = compile ps_2_0 main();
    }
}