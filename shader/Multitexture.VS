struct VS_INPUT {
    float3 position : POSITION;
    float2 texcoord : TEXCOORD;
};

struct PS_INPUT {
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
};

cbuffer ConstantBuffer : register(b0) {
    matrix world;
    matrix view;
    matrix projection;
};

PS_INPUT VS_Main(VS_INPUT input) {
    PS_INPUT output;
    output.position = mul(float4(input.position, 1.0f), world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    output.texcoord = input.texcoord;
    return output;
}