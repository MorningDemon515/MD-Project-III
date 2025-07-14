#include "Texture.h"

#include "Main.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

extern ID3D11Device* Device;
extern ID3D11DeviceContext* Context;

extern HWND WindowHanled;

void Texture::LoadFile(const char* file)
{
    int width, height, channels;
    unsigned char* image = stbi_load(file, & width, & height, & channels, STBI_rgb_alpha);

    if (!image)
    {
        ErrorMessage_2(WindowHanled, "Cann't Load File");
    }

    D3D11_TEXTURE2D_DESC desc = { 0 };
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA t_initData = { 0 };
    t_initData.pSysMem = image;
    t_initData.SysMemPitch = width * 4;

    Device->CreateTexture2D(&desc, &t_initData, &texture);
    stbi_image_free(image);

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = desc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    Device->CreateShaderResourceView(texture, &srvDesc, &textureView);

    D3D11_SAMPLER_DESC sampDesc = {};
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    Device->CreateSamplerState(&sampDesc, &samplerState);
}

Texture::~Texture()
{
	texture->Release();
	textureView->Release();
	samplerState->Release();
}

void Texture::Set()
{
    Context->PSSetShaderResources(0, 1, &textureView);
    Context->PSSetSamplers(0, 1, &samplerState);
}

MultiTexture::~MultiTexture()
{
    texture1->Release();
    textureView1->Release();

    texture2->Release();
    textureView2->Release();

    samplerState->Release();
}

void MultiTexture::LoadFile(const char* f1, const char* f2)
{
    int width1, height1, channels1;
    unsigned char* image1 = stbi_load(f1, &width1, &height1, &channels1, STBI_rgb_alpha);
    if (!image1)
    {
        ErrorMessage_2(WindowHanled, "Canm't Load File");
    }

    D3D11_TEXTURE2D_DESC desc1 = { 0 };
    desc1.Width = width1;
    desc1.Height = height1;
    desc1.MipLevels = 1;
    desc1.ArraySize = 1;
    desc1.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc1.SampleDesc.Count = 1;
    desc1.Usage = D3D11_USAGE_DEFAULT;
    desc1.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc1.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA t_initData1 = { 0 };
    t_initData1.pSysMem = image1;
    t_initData1.SysMemPitch = width1 * 4;

    Device->CreateTexture2D(&desc1, &t_initData1, &texture1);
    stbi_image_free(image1);

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc1 = {};
    srvDesc1.Format = desc1.Format;
    srvDesc1.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc1.Texture2D.MipLevels = 1;

    Device->CreateShaderResourceView(texture1, &srvDesc1, &textureView1);

    int width2, height2, channels2;
    unsigned char* image2 = stbi_load(f2, &width2, &height2, &channels2, STBI_rgb_alpha);
    if (!image2)
    {
        ErrorMessage_2(WindowHanled, "Canm't Load File");
    }

    D3D11_TEXTURE2D_DESC desc2 = { 0 };
    desc2.Width = width2;
    desc2.Height = height2;
    desc2.MipLevels = 1;
    desc2.ArraySize = 1;
    desc2.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc2.SampleDesc.Count = 1;
    desc2.Usage = D3D11_USAGE_DEFAULT;
    desc2.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc2.CPUAccessFlags = 0;
    
    D3D11_SUBRESOURCE_DATA t_initData2 = { 0 };
    t_initData2.pSysMem = image2;
    t_initData2.SysMemPitch = width2 * 4;

    Device->CreateTexture2D(&desc2, &t_initData2, &texture2);
    stbi_image_free(image2);

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc2 = {};
    srvDesc2.Format = desc2.Format;
    srvDesc2.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc2.Texture2D.MipLevels = 1;

    Device->CreateShaderResourceView(texture2, &srvDesc2, &textureView2);

    D3D11_SAMPLER_DESC sampDesc = {};
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    Device->CreateSamplerState(&sampDesc, &samplerState);
}

void MultiTexture::Set()
{
    ID3D11ShaderResourceView* textures[2] = { textureView1, textureView2 };
    Context->PSSetShaderResources(0, 2, textures); 
    Context->PSSetSamplers(0, 1, &samplerState);

}