#include "Rectangle.h"

#include "../Shader.h"
#include <dxgi.h>

#include "../Main.h"

extern ID3D11Device* Device;
extern ID3D11DeviceContext* Context;

struct Rectangle_Vertex {
    float x, y, z;
};

const D3D11_INPUT_ELEMENT_DESC Rectangle_InputLayout[1] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

Rectangle_::Rectangle_()
{
    Rectangle_Vertex vertices[] = {
        { -0.5f,0.5f,0.0f},
        { 0.5f,0.5f,0.0f},
        { -0.5f,-0.5f,0.0f},
        { 0.5f,-0.5f,0.0f}
    };

    D3D11_BUFFER_DESC vbd = { 0 };
    vbd.ByteWidth = sizeof(vertices);
    vbd.Usage = D3D11_USAGE_DEFAULT;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = { 0 };
    initData.pSysMem = vertices;

    Device->CreateBuffer(&vbd, &initData, &RectangleBuffer);

    WORD indices[] = { 0,1,2, 1,3,2 };

    D3D11_BUFFER_DESC ibDesc = {};
    ibDesc.Usage = D3D11_USAGE_IMMUTABLE;
    ibDesc.ByteWidth = sizeof(indices);
    ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA ibInitData = {};
    ibInitData.pSysMem = indices;

    Device->CreateBuffer(&ibDesc, &ibInitData, &IndexBuffer);

}

Rectangle_::~Rectangle_()
{
    RectangleBuffer->Release();
    IndexBuffer->Release();
}

void Rectangle_::Draw()
{
    Shader shader = Shader("shader/Triangle.VS", "shader/Triangle.PS",
        "VS_Main", "PS_Main");

    shader.SetVertexShader(Rectangle_InputLayout, 1);
    shader.SetPixelShader();

    UINT stride = sizeof(Rectangle_Vertex);
    UINT offset = 0;
    Context->IASetVertexBuffers(0, 1, &RectangleBuffer, &stride, &offset);
    Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Context->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    Context->DrawIndexed(6, 0, 0);

}