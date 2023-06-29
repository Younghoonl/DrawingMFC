#pragma once
#include "CMyShape.h"
class CMyCurve :
    public CMyShape
{
    CList<CPoint> m_pts;
    bool PtInLine(CPoint p1, CPoint p2, CPoint p);
public:
    CMyCurve(CPoint point);
    void draw(CDC& dc);
    void update(CPoint point);
    CRect CMyCurve::getBbox();
    bool pointCollision(CPoint point);
    void offset(CPoint point);
};

