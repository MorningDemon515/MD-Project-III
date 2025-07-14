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

//extern ID3D11RasterizerState* rsState;

extern ID3D11BlendState* BlendState;

void InitGraphics();
void Clean_Graphics();

Cube cube = Cube();

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
    //Context->RSSetState(rsState);
    Context->ClearRenderTargetView(RenderTargetView, clearColor);
    Context->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    UINT sampleMask = 0xffffffff;
    Context->OMSetBlendState(BlendState, blendFactor, sampleMask);

    MD_MATH_MATRIX Rx, Ry;

    Rx = MD_Math_RotationMatrix(MD_MATH_PI_4,'X');

    static float y = 0.0f;
    Ry = MD_Math_RotationMatrix(y,'Y');
    y += TimeDelta();

    if (y >= MD_MATH_PI)
        y = 0.0f;

    MD_MATH_MATRIX WorldMatrix = MD_Math_MatrixMulMatrix(Rx,Ry);

    MD_MATH_VECTOR3 eye = { 0.0f, 0.0f, -5.0f };
    MD_MATH_VECTOR3 target = { 0.0f, 0.0f, 0.0f };
    MD_MATH_VECTOR3 up = { 0.0f, 1.0f, 0.0f };

    cube.Draw(WorldMatrix,
        MD_Math_ViewMatrixLH(
            eye ,
            target,
            up));
    

    /*
    MD_MATH_MATRIX WorldMatrix = MD_Math_IdentityMatrix;

    MD_MATH_VECTOR3 eye = { 0.0f, 0.0f, -5.0f };
    MD_MATH_VECTOR3 target = { 0.0f, 0.0f, 0.0f };
    MD_MATH_VECTOR3 up = { 0.0f, 1.0f, 0.0f };

    Rectangle_ rt = Rectangle_();
    rt.Draw(WorldMatrix,
        MD_Math_ViewMatrixLH(
            eye,
            target,
            up));
            */

    SwapChain->Present(0, 0);
}