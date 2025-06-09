#include "Main.h"
#include <d3d11.h>
#include <dxgi.h>

#include "Scene.h"

#include "Figures/Triangle.h"
#include "Figures/Rectangle.h"
#include "Figures/Cube.h"

extern ID3D11Device* Device;
extern ID3D11DeviceContext* Context;
extern IDXGISwapChain* SwapChain;

extern ID3D11RenderTargetView* RenderTargetView;
extern ID3D11DepthStencilView* DepthStencilView;

extern ID3D11RasterizerState* rsState;

void InitGraphics();
void Clean_Graphics();

Scene::Scene()
{
    InitGraphics();
}

Scene::~Scene()
{
    Clean_Graphics();
}

void Scene::Draw()
{
    float clearColor[4] = { 0.2f, 0.4f, 0.6f, 1.0f };
    Context->RSSetState(rsState);
    Context->ClearRenderTargetView(RenderTargetView, clearColor);
    Context->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    Cube cube = Cube();
    
    MyMatrix WorldMatrix = {
        1.0f,0.0f, 0.0f,1.0f,
        0.0f,1.0f,0.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,0.0f,1.0f
    };

    cube.Draw(WorldMatrix,
        XMMatrixLookAtLH(
            XMVectorSet(0.0f, 0.0f, -5.0f, 1.0f),
            XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
            XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f)));

    SwapChain->Present(0, 0);
}