#include "Samplers.hlsli"
#include "Textures.hlsli"

struct VSInput {
    float3 pos : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct VSOutput {
    float4 pos : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

float4 main(VSOutput input) : SV_Target
{
    float brightness = 2.8f; // 밝기 계수 (1.0은 원본 밝기)
    float contrast = 1.0f;   // 대비 계수 (1.0은 원본 대비)

    // 텍스처에서 색상을 샘플링
    float4 color = sprite.Sample(anisotropicSampler, input.uv);

    // 밝기 조절
    color.rgb *= brightness;

    // 대비 조절
    color.rgb = ((color.rgb - 0.5f) * contrast) + 0.5f;

    return color;
}
