#ifndef CUBE_H
#define CUBE_H

#include <d3d11.h>

#include <DirectXMath.h>

using namespace DirectX;

struct MyMatrix
{
    float m[16];
};

class Cube
{
private:
    ID3D11Buffer* CubeBuffer;

public:
    Cube();
    ~Cube();

    void Draw(MyMatrix WorldMatrix, XMMATRIX ViewMatrix);

};


#endif