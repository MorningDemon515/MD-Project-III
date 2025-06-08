#ifndef CUBE_H
#define CUBE_H

#include <d3d11.h>

#include <DirectXMath.h>

using namespace DirectX;

class Cube
{
private:
    ID3D11Buffer* CubeBuffer;

public:
    Cube();
    ~Cube();

    void Draw(XMMATRIX WorldMatrix, XMMATRIX ViewMatrix);

};


#endif