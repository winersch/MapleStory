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
    float brightness = 2.8f; // ��� ��� (1.0�� ���� ���)
    float contrast = 1.0f;   // ��� ��� (1.0�� ���� ���)

    // �ؽ�ó���� ������ ���ø�
    float4 color = sprite.Sample(anisotropicSampler, input.uv);

    // ��� ����
    color.rgb *= brightness;

    // ��� ����
    color.rgb = ((color.rgb - 0.5f) * contrast) + 0.5f;

    return color;
}
