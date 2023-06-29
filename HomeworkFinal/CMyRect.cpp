#include "pch.h"
#include "CMyRect.h"


CMyRect::CMyRect(CPoint point) : CMyShape(point) {
}


void CMyRect::draw(CDC& dc) {
	CMyShape::draw(dc);
	dc.Rectangle(getBbox());
}


void CMyRect::update(CPoint point) {
	CMyShape::update(point);
	m_startPoint.x = min(m_startPoint.x, point.x);
	m_startPoint.y = min(m_startPoint.y, point.y);
}


CRect CMyRect::getBbox() {
	return CRect(m_startPoint, m_endPoint + CPoint(1, 1));
}


bool CMyRect::pointCollision(CPoint point) {
	return getBbox().PtInRect(point);
}