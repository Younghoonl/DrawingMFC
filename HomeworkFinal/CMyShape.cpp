#include "pch.h"
#include "CMyShape.h"

CMyShape::CMyShape(CPoint point) : m_startPoint(point), m_endPoint(point) {
	COLORREF pen_color = RGB(rand() % 128, rand() % 128, rand() % 128);
	COLORREF brush_color = pen_color + RGB(128, 128, 128);
	m_pen.CreatePen(PS_SOLID, 3, pen_color);
	m_brush.CreateSolidBrush(brush_color);
}


void CMyShape::draw(CDC& dc) {
	dc.SelectObject(m_pen);
	dc.SelectObject(m_brush);
}


void CMyShape::update(CPoint point) {
	m_endPoint = point;
}


bool CMyShape::rectCollision(CRect rect) {
	CRect bbox = getBbox();
	bbox.NormalizeRect();
	rect.NormalizeRect();
	CRect intersection;
	intersection.IntersectRect(bbox, rect);
	return intersection.EqualRect(bbox);
}


void CMyShape::offset(CPoint point) {
	m_startPoint += point;
	m_endPoint += point;
}


void CMyShape::ungroup(CList<CMyShape*>& children) {
}