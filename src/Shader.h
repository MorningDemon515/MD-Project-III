#ifndef SHADER_H
#define SHADER_H

#include <d3d11.h>
#include <d3dcompiler.h>

class Shader
{
private:
    ID3DBlob* VSBlob;
    ID3DBlob* PSBlob;

    ID3D11VertexShader* VertexShader;
    ID3D11PixelShader* PixelShader;

    ID3D11InputLayout* InputLayout;
public:

    Shader() {};
    Shader(const char* VSS, const char* PSS, const char* VS_Main, const char* PS_Main);
    ~Shader();

    void SetVertexShader(const D3D11_INPUT_ELEMENT_DESC* layout, int num);
    void SetPixelShader();
};

class ConstantBuffer
{
public:
    ConstantBuffer() {};
    ConstantBuffer(UINT Size);
    ~ConstantBuffer();

    void Begin();

    void End();

    void Set();

    D3D11_MAPPED_SUBRESOURCE mappedResource;
private:
    ID3D11Buffer* CBuffer;

};


#endif