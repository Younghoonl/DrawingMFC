#include "pch.h"
#include "CMyCircle.h"


CMyCircle::CMyCircle(CPoint point) : CMyShape(point) {
}


void CMyCircle::draw(CDC& dc) {
	CMyShape::draw(dc);
	dc.Ellipse(getBbox());
}


CRect CMyCircle::getBbox() {
	int radius = static_cast<int>(hypot(m_startPoint.x - m_endPoint.x, m_startPoint.y - m_endPoint.y));
	radius = max(radius, 1);
	CPoint p(radius, radius);
	return CRect(CRect(m_startPoint + -p, m_startPoint + p));
}


bool CMyCircle::pointCollision(CPoint point) {
	int radius1 = static_cast<int>(hypot(m_startPoint.x - point.x, m_startPoint.y - point.y));
	int radius2 = static_cast<int>(hypot(m_startPoint.x - m_endPoint.x, m_startPoint.y - m_endPoint.y));
	return radius1 <= radius2;
}