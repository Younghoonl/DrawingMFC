#pragma once
#include "CMyShape.h"
class CMyCircle :
    public CMyShape
{
public:
    CMyCircle(CPoint point);
    void draw(CDC& dc);
    CRect CMyCircle::getBbox();
    bool pointCollision(CPoint point);
};

