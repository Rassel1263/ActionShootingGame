Texture2D SpriteTexture;
float2 xTextureSize : VPOS;
//밝기 늘릴 강도
float4 AppendColor = float4(0.8, 0.8, 0.8, 0.8);
//외곽 글로우 강도
float xOutGlowColor = 2;

sampler2D InputSampler = sampler_state
{
    Texture = <SpriteTexture>;
};

struct VertexShaderOutput
{
    float3 Position : POSITION;
    float4 Color : COLOR0;
    float2 UV : TEXCOORD0;
};

float2 filter(float2 input) {
    return float2(saturate(input.x), saturate(input.y));
}

float4 main(VertexShaderOutput input) : COLOR
{
    float4 currentPixel = tex2D(InputSampler, input.UV) * input.Color;
    float4 output = float4(1, 1, 1, currentPixel.a);

    
    if (currentPixel.a > 0) {
        return currentPixel + AppendColor;
    }

    float2 uvPix = float2(4 / xTextureSize.x, 4 / xTextureSize.y);

    output += tex2D(InputSampler, float2(input.UV.x, input.UV.y)) * 0.3;

    for(int i = 1; i <= 1; ++i) {
        float color = 0;

        color += tex2D(InputSampler, filter(float2((i * uvPix.x) + input.UV.x, (0 * uvPix.y) + input.UV.y))).a;
        color += tex2D(InputSampler, filter(float2((0 * uvPix.x) + input.UV.x, (i * uvPix.y) + input.UV.y))).a;
        color += tex2D(InputSampler, filter(float2((-i * uvPix.x) + input.UV.x, (0 * uvPix.y) + input.UV.y))).a;
        color += tex2D(InputSampler, filter(float2((0 * uvPix.x) + input.UV.x, (-i * uvPix.y) + input.UV.y))).a;
        color += tex2D(InputSampler, filter(float2((i * uvPix.x) + input.UV.x, (i * uvPix.y) + input.UV.y))).a;
        color += tex2D(InputSampler, filter(float2((i * uvPix.x) + input.UV.x, (-i * uvPix.y) + input.UV.y))).a;
        color += tex2D(InputSampler, filter(float2((-i * uvPix.x) + input.UV.x, (i * uvPix.y) + input.UV.y))).a;
        color += tex2D(InputSampler, filter(float2((-i * uvPix.x) + input.UV.x, (-i * uvPix.y) + input.UV.y))).a;
        
        output.a += color * 0.1 * 0.125;
    }

    if (output.a > 0) output.a *= xOutGlowColor;

    return output;
}

technique Outline
{
    pass pass0
    {
        PixelShader = compile ps_2_0 main();
    }
};