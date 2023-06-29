#pragma once
class CMyShape
{
public:
	CMyShape(CPoint point);
	CPoint m_startPoint;
	CPoint m_endPoint;
	CPen m_pen;
	CBrush m_brush;
	virtual void draw(CDC& dc);
	virtual void update(CPoint point);
	virtual CRect getBbox() = 0;
	bool rectCollision(CRect rect);
	virtual bool pointCollision(CPoint point) = 0;
	virtual void offset(CPoint point);
	virtual void ungroup(CList<CMyShape*>& children);
};