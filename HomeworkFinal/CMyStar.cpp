#include "pch.h"
#include "CMyStar.h"


CMyStar::CMyStar(CPoint point) : CMyShape(point) {
}


CPoint* CMyStar::getPts() {
	static CPoint p[10];
	const double PI = 3.14159265358979;
	double radius = hypotl(m_startPoint.x - m_endPoint.x, m_startPoint.y - m_endPoint.y);
	double radius2 = radius * cos(0.2 * 2 * PI) / cos(0.1 * 2 * PI);
	radius = max(radius, 1);
	radius2 = max(radius2, 1);
	for (int i = 0; i < 10; ++i) {
		double r = i % 2 == 0 ? radius : radius2;
		int x = static_cast<int>(cos((i / 10.0 + 0.75) * 2 * PI) * r);
		int y = static_cast<int>(sin((i / 10.0 + 0.75) * 2 * PI) * r);
		p[i] = m_startPoint + CPoint(x, y);
	}
	return p;
}


void CMyStar::draw(CDC& dc) {
	CMyShape::draw(dc);
	dc.Polygon(getPts(), 10);
}


CRect CMyStar::getBbox() {
	CPoint* p = getPts();
	CRect rect(m_startPoint, m_startPoint);
	for (int i = 0; i < 10; ++i) {
		rect.left = min(rect.left, p[i].x);
		rect.top = min(rect.top, p[i].y);
		rect.right = max(rect.right, p[i].x);
		rect.bottom = max(rect.bottom, p[i].y);
	}
	return rect;
}


bool CMyStar::pointCollision(CPoint point) {
	CRgn rgn;
	rgn.CreatePolygonRgn(getPts(), 10, ALTERNATE);
	return rgn.PtInRegion(point);
}