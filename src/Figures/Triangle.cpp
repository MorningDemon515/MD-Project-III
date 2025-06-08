#include "Triangle.h"

#include "../Shader.h"
#include <dxgi.h>

#include "../Main.h"

extern ID3D11Device* Device;
extern ID3D11DeviceContext* Context;

struct Triangle_Vertex {
    float x, y, z;
};

const D3D11_INPUT_ELEMENT_DESC Triangle_InputLayout[1] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

Triangle::Triangle(float* pos)
{
    Triangle_Vertex vertices[] = {
        {  pos[0],  pos[1], pos[2]},
        {  pos[3],  pos[4], pos[5]},
        {  pos[6],  pos[7], pos[8]},
    };

    D3D11_BUFFER_DESC vbd = { 0 };
    vbd.ByteWidth = sizeof(vertices);
    vbd.Usage = D3D11_USAGE_DEFAULT;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = { 0 };
    initData.pSysMem = vertices;

    Device->CreateBuffer(&vbd, &initData, &TriangleBuffer);

}

Triangle::~Triangle()
{
    TriangleBuffer->Release();

}

void Triangle::Draw()
{
    Shader shader = Shader("shader/Triangle.VS", "shader/Triangle.PS",
        "VS_Main", "PS_Main");

    shader.SetVertexShader(Triangle_InputLayout, 1);
    shader.SetPixelShader();

    UINT stride = sizeof(Triangle_Vertex);
    UINT offset = 0;
    Context->IASetVertexBuffers(0, 1, &TriangleBuffer, &stride, &offset);
    Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Context->Draw(3, 0);

}