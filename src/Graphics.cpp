#include "Main.h"
#include <d3d11.h>
#include <dxgi.h>

extern HWND WindowHanled;

ID3D11Device* Device;
ID3D11DeviceContext* Context;
IDXGISwapChain* SwapChain;

ID3D11RenderTargetView* RenderTargetView;
ID3D11DepthStencilView* DepthStencilView;

//ID3D11RasterizerState* rsState;
ID3D11BlendState* BlendState = nullptr;

void InitGraphics()
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
    sd.BufferDesc.Width = WINDOW_WIDTH;
    sd.BufferDesc.Height = WINDOW_HEIGHT;
    sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 0;
    sd.BufferDesc.RefreshRate.Denominator = 0;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 1;
    sd.OutputWindow = WindowHanled;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = 0;

    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &sd,
        &SwapChain,
        &Device,
        nullptr,
        &Context
    );

    if (!Device)
        ErrorMessage_2(WindowHanled, "Create Device Failed!");

    if (!SwapChain)
        ErrorMessage_2(WindowHanled, "Create SwapChain Failed!");

    if (!Context)
        ErrorMessage_2(WindowHanled, "Create Context Failed!");

    ID3D11Texture2D* BackBuffer;

    SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

    if (!BackBuffer)
        ErrorMessage_2(WindowHanled, "Get Back Buffer Failed!");

    Device->CreateRenderTargetView(BackBuffer, nullptr, &RenderTargetView);

    if (!RenderTargetView)
        ErrorMessage_2(WindowHanled, "Create Render Target View Failed!");

    BackBuffer->Release();

    ID3D11Texture2D* DepthStencilBuffer;

    D3D11_TEXTURE2D_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));
    depthStencilDesc.Width = WINDOW_WIDTH;
    depthStencilDesc.Height = WINDOW_HEIGHT;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;

    Device->CreateTexture2D(&depthStencilDesc, nullptr, &DepthStencilBuffer);
    if (!DepthStencilBuffer)
        ErrorMessage_2(WindowHanled, "Create Depth Stencil Buffer Failed!");

    Device->CreateDepthStencilView(DepthStencilBuffer, nullptr, &DepthStencilView);
    DepthStencilBuffer->Release();

    Context->OMSetRenderTargets(1, &RenderTargetView, DepthStencilView);

    //D3D11_RASTERIZER_DESC rsDesc = {};
    //rsDesc.FillMode = D3D11_FILL_SOLID;
    //rsDesc.CullMode = D3D11_CULL_NONE;
    //rsDesc.FrontCounterClockwise = FALSE;

    //Device->CreateRasterizerState(&rsDesc, &rsState);

    D3D11_BLEND_DESC blendDesc = {};
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.IndependentBlendEnable = false;

    blendDesc.RenderTarget[0].BlendEnable = true;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;        
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;  
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;          
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;         
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;       
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;       
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; 

    Device->CreateBlendState(&blendDesc, &BlendState);

    D3D11_VIEWPORT vp;
    vp.Width = WINDOW_WIDTH; vp.Height = WINDOW_HEIGHT;
    vp.MinDepth = 0.0f; vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0; vp.TopLeftY = 0;
    Context->RSSetViewports(1, &vp);

    SetWindowTextA(WindowHanled, "MDP-III - Direct3D 11");
}

void Clean_Graphics()
{
    //rsState->Release();
    BlendState->Release();

	RenderTargetView->Release();
	DepthStencilView->Release();

	Device->Release();
	SwapChain->Release();
	Context->Release();
}

