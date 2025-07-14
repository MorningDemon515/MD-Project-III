#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <d3d11.h>

#include "../MD_Math.h"

class Rectangle_
{
private:
    ID3D11Buffer* RectangleBuffer;
    ID3D11Buffer* IndexBuffer;

public:
    Rectangle_();
    ~Rectangle_();

    void Draw(MD_MATH_MATRIX WorldMatrix, MD_MATH_MATRIX  ViewMatrix);

};


#endif