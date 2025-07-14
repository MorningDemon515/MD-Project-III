#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

extern ID3D11Device* Device;
extern ID3D11DeviceContext* Context;

void Texture::LoadFile(const char* file)
{
    int width, height, channels;
    unsigned char* image = stbi_load(file, & width, & height, & channels, STBI_rgb_alpha);

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