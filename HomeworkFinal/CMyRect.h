#pragma once
#include "CMyShape.h"
class CMyRect :
    public CMyShape
{
public:
    CMyRect(CPoint point);
    void draw(CDC& dc);
    void update(CPoint point);
    CRect getBbox();
    bool pointCollision(CPoint point);
};

