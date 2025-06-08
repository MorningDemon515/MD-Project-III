#include "Shader.h"

#include "Main.h"

#include <iostream>
#include <string>

extern HWND WindowHanled;

extern ID3D11Device* Device;
extern ID3D11DeviceContext* Context;

std::wstring CharToWchar(const char* src) {
    int bufferSize = MultiByteToWideChar(CP_ACP, 0, src, -1, nullptr, 0);
    if (bufferSize == 0) return L"";

    std::wstring result(bufferSize, L'\0');
    MultiByteToWideChar(CP_ACP, 0, src, -1, &result[0], bufferSize);
    result.resize(bufferSize - 1); //
    return result;
}

Shader::Shader(const char* VSS, const char* PSS, const char* VS_Main, const char* PS_Main)
{
    HRESULT hr = D3DCompileFromFile(
        CharToWchar(VSS).c_str(),
        nullptr,
        nullptr,
        VS_Main,
        "vs_5_0",
        D3DCOMPILE_DEBUG,
        0,
        &VSBlob,
        nullptr
    );

    if (FAILED(hr))
    {
        ErrorMessage_2(WindowHanled, "Compiler Vertex Shader Source Failed!");
    }

    hr = D3DCompileFromFile(
        CharToWchar(PSS).c_str(),
        nullptr,
        nullptr,
        PS_Main,
        "ps_5_0",
        D3DCOMPILE_DEBUG,
        0,
        &PSBlob,
        nullptr
    );

    if (FAILED(hr))
    {
        ErrorMessage_2(WindowHanled, "Compiler Pixel Shader Source Failed!");
    }
}

Shader::~Shader()
{
    VertexShader->Release();
    PixelShader->Release();

    InputLayout->Release();
}

void Shader::SetVertexShader(const D3D11_INPUT_ELEMENT_DESC* layout, int num)
{
    Device->CreateVertexShader(VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), nullptr, &VertexShader);
    Context->VSSetShader(VertexShader, nullptr, 0);

    Device->CreateInputLayout(layout, num, VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), &InputLayout);
    Context->IASetInputLayout(InputLayout);
    VSBlob->Release();
}

void Shader::SetPixelShader()
{
    Device->CreatePixelShader(PSBlob->GetBufferPointer(), PSBlob->GetBufferSize(), nullptr, &PixelShader);
    Context->PSSetShader(PixelShader, nullptr, 0);
    PSBlob->Release();
}

ConstantBuffer::ConstantBuffer(UINT size)
{
    D3D11_BUFFER_DESC cbd;
    ZeroMemory(&cbd, sizeof(D3D11_BUFFER_DESC));
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.ByteWidth = size;
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    Device->CreateBuffer(&cbd, nullptr, &CBuffer);
}

ConstantBuffer::~ConstantBuffer()
{
    CBuffer->Release();
}

void ConstantBuffer::Set()
{

    Context->VSSetConstantBuffers(0, 1, &CBuffer);
}

void ConstantBuffer::Begin()
{
    Context->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
}

void ConstantBuffer::End()
{
    Context->Unmap(CBuffer, 0);
}