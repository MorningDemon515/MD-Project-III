cbuffer MatrixBuffer : register(b0) {
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
};

struct VS_INPUT {
    float3 pos : POSITION;
	float2 texcoord : TEXCOORD;
};

struct VS_OUTPUT {
    float4 pos : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

VS_OUTPUT VS_Main(VS_INPUT input)
{
    VS_OUTPUT output;
    float4 worldPos = mul(float4(input.pos, 1.0), World);
    float4 viewPos = mul(worldPos, View);
    output.pos = mul(viewPos, Projection);
	output.texcoord = input.texcoord;
    return output;
}