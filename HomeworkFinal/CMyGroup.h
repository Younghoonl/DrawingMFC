#pragma once
#include "CMyShape.h"
class CMyGroup :
    public CMyShape
{
	CList<CMyShape*> m_children;
public:
	CMyGroup(const CList<CMyShape*>& children);
	void draw(CDC& dc);
	void update(CPoint point);
	CRect getBbox();
	bool pointCollision(CPoint point);
	void offset(CPoint point);
	void ungroup(CList<CMyShape*>& children);
};

