#include "Main.h"
#include <d3d11.h>
#include <dxgi.h>

#include "Scene.h"

#include "Figures/Triangle.h"
#include "Figures/Rectangle.h"

extern ID3D11Device* Device;
extern ID3D11DeviceContext* Context;
extern IDXGISwapChain* SwapChain;

extern ID3D11RenderTargetView* RenderTargetView;
extern ID3D11DepthStencilView* DepthStencilView;

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
    Context->ClearRenderTargetView(RenderTargetView, clearColor);
    Context->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    Rectangle_ rc = Rectangle_();
    rc.Draw();

    SwapChain->Present(0, 0);
}