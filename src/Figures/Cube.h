#ifndef CUBE_H
#define CUBE_H

#include <d3d11.h>

#include "../MD_Math.h"

class Cube
{
private:
    ID3D11Buffer* CubeBuffer;

public:
    Cube();
    ~Cube();

    void Draw(MD_MATH_MATRIX WorldMatrix, MD_MATH_MATRIX ViewMatrix);

};


#endif