#include "Rectangle.h"

#include "../Shader.h"
#include <dxgi.h>

#include "../Main.h"

#include "../Texture.h"

extern ID3D11Device* Device;
extern ID3D11DeviceContext* Context;

MultiTexture tex = MultiTexture();

struct Rectangle_Vertex {
    float x, y, z;
    float u, v;
};

struct Rectangle_MatrixBufferType {
    MD_MATH_MATRIX World;
    MD_MATH_MATRIX View;
    MD_MATH_MATRIX Projection;
};

const D3D11_INPUT_ELEMENT_DESC Rectangle_InputLayout[2] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

Rectangle_::Rectangle_()
{
    tex.LoadFile("resources/image.png","resources/image.jpg");
    Rectangle_Vertex vertices[] = {
        { -0.5f,0.5f,0.0f,  0.0f,0.0f},
        { 0.5f,0.5f,0.0f,   1.0f,0.0f},
        { -0.5f,-0.5f,0.0f, 0.0f,1.0f},
        { 0.5f,-0.5f,0.0f,  1.0f,1.0f}
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

void Rectangle_::Draw(MD_MATH_MATRIX WorldMatrix, MD_MATH_MATRIX  ViewMatrix)
{
    Shader shader = Shader("shader/Multitexture.VS", "shader/Multitexture.PS",
        "VS_Main", "PS_Main");

    ConstantBuffer cbuffer = ConstantBuffer(sizeof(Rectangle_MatrixBufferType));

    cbuffer.Begin();

    Rectangle_MatrixBufferType* dataPtr = (Rectangle_MatrixBufferType*)cbuffer.mappedResource.pData;

    dataPtr->World = WorldMatrix;
    dataPtr->View = ViewMatrix;
    dataPtr->Projection = MD_Math_PerspectiveMatrixLH(
        MD_Math_AngularToRadian(45.0f),
        (float)WINDOW_WIDTH / (float) WINDOW_HEIGHT,
        0.1f,
        100.0f
    );

    cbuffer.End();
    cbuffer.Set();

    shader.SetVertexShader(Rectangle_InputLayout, 2);
    shader.SetPixelShader();

    UINT stride = sizeof(Rectangle_Vertex);
    UINT offset = 0;
    Context->IASetVertexBuffers(0, 1, &RectangleBuffer, &stride, &offset);
    Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Context->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    tex.Set();

    Context->DrawIndexed(6, 0, 0);

}