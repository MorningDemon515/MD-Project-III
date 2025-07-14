#include "Cube.h"

#include "../Shader.h"
#include <dxgi.h>

#include "../Main.h"

extern ID3D11Device* Device;
extern ID3D11DeviceContext* Context;

struct Cube_Vertex {
    float x, y, z;
};

struct MatrixBufferType {
    MD_MATH_MATRIX World;
    MD_MATH_MATRIX View;
    MD_MATH_MATRIX Projection;
};

const D3D11_INPUT_ELEMENT_DESC Cube_InputLayout[1] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

Cube::Cube()
{
    Cube_Vertex vertices[] = {

        {-0.5f, -0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},

        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f},

        {-0.5f, -0.5f, -0.5f},
        {-0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f},

        {0.5f, -0.5f, -0.5f},
        {0.5f,  0.5f, -0.5f},
        {0.5f,  0.5f,  0.5f},
        {0.5f, -0.5f, -0.5f},
        {0.5f,  0.5f,  0.5f},
        {0.5f, -0.5f,  0.5f},

        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f,  0.5f},
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f,  0.5f},
        {-0.5f, -0.5f,  0.5f},

        {-0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f, -0.5f},
        { 0.5f,  0.5f,  0.5f},
        { 0.5f,  0.5f, -0.5f}
    };

    D3D11_BUFFER_DESC vbd = { 0 };
    vbd.ByteWidth = sizeof(vertices);
    vbd.Usage = D3D11_USAGE_DEFAULT;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = { 0 };
    initData.pSysMem = vertices;

    Device->CreateBuffer(&vbd, &initData, &CubeBuffer);

}

Cube::~Cube()
{
    CubeBuffer->Release();

}

void Cube::Draw(MD_MATH_MATRIX WorldMatrix, MD_MATH_MATRIX  ViewMatrix)
{
    Shader shader = Shader("shader/Cube.VS", "shader/Cube.PS",
        "VS_Main", "PS_Main");

    shader.SetVertexShader(Cube_InputLayout, 1);
    shader.SetPixelShader();

    MD_MATH_MATRIX viewMatrix = ViewMatrix;

    MD_MATH_MATRIX projectionMatrix = MD_Math_PerspectiveMatrixLH(
        MD_Math_AngularToRadian(45.0f),
        (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
        0.1f,
        100.0f
    );

    ConstantBuffer cbuffer = ConstantBuffer(sizeof(MatrixBufferType));

    cbuffer.Begin();

    MatrixBufferType* dataPtr = (MatrixBufferType*)cbuffer.mappedResource.pData;

    dataPtr->World = WorldMatrix;
    dataPtr->View = viewMatrix;
    dataPtr->Projection = projectionMatrix;

    cbuffer.End();
    cbuffer.Set();

    UINT stride = sizeof(Cube_Vertex);
    UINT offset = 0;
    Context->IASetVertexBuffers(0, 1, &CubeBuffer, &stride, &offset);
    Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Context->Draw(36, 0);

}