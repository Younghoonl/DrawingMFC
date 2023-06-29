#pragma once
#include "CMyShape.h"
class CMyStar :
    public CMyShape
{
    CPoint* getPts();
public:
    CMyStar(CPoint point);
    void draw(CDC& dc);
    CRect CMyStar::getBbox();
    bool pointCollision(CPoint point);
};

