#include "pch.h"
#include "CMyCurve.h"


CMyCurve::CMyCurve(CPoint point) : CMyShape(point) {
}


void CMyCurve::draw(CDC& dc) {
	CMyShape::draw(dc);
	dc.MoveTo(m_startPoint);
	POSITION pos = m_pts.GetHeadPosition();
	while (pos) {
		dc.LineTo(m_pts.GetNext(pos));
	}
	dc.LineTo(m_endPoint);
}


void CMyCurve::update(CPoint point) {
	CMyShape::update(point);
	m_pts.AddTail(point);
}


CRect CMyCurve::getBbox() {
	CRect rect(m_startPoint, m_startPoint);
	rect.InflateRect(1, 1);
	POSITION pos = m_pts.GetHeadPosition();
	while (pos) {
		CPoint p = m_pts.GetNext(pos);
		rect.left = min(rect.left, p.x - 1);
		rect.top = min(rect.top, p.y - 1);
		rect.right = max(rect.right, p.x + 1);
		rect.bottom = max(rect.bottom, p.y + 1);
	}
	return rect;
}


bool CMyCurve::PtInLine(CPoint p1, CPoint p2, CPoint p) {
	static const int d = 6;
	static const CPoint dpoint[4] = {
		CPoint(d, d), CPoint(d, -d), CPoint(-d, -d), CPoint(-d, d)
	};
	CRgn rgn;
	CPoint pts[6];
	int initDir;
	if (p1.x <= p2.x && p1.y <= p2.y) {
		initDir = 1;
	}
	else if (p1.x <= p2.x && p1.y > p2.y) {
		initDir = 2;
	}
	else if (p1.x > p2.x && p1.y > p2.y) {
		initDir = 3;
	}
	else if (p1.x > p2.x && p1.y <= p2.y) {
		initDir = 0;
	}
	for (int i = 0; i < 3; ++i) {
		pts[i] = p1 + dpoint[(initDir + i) % 4];
	}
	for (int i = 0; i < 3; ++i) {
		pts[i + 3] = p2 + dpoint[(initDir + i + 2) % 4];
	}
	rgn.CreatePolygonRgn(pts, 6, WINDING);
	return rgn.PtInRegion(p);
}


bool CMyCurve::pointCollision(CPoint point) {
	POSITION pos = m_pts.GetHeadPosition();
	if (!pos) {
		CRect rect(m_startPoint.x - 2, m_startPoint.y - 2, m_startPoint.x + 2, m_startPoint.y + 2);
		return rect.PtInRect(point);
	}
	CPoint p = m_pts.GetNext(pos);
	if (PtInLine(m_startPoint, p, point)) {
		return true;
	}
	while (pos) {
		CPoint pNxt = m_pts.GetNext(pos);
		if (PtInLine(p, pNxt, point)) {
			return true;
		}
		p = pNxt;
	}
	return false;
}


void CMyCurve::offset(CPoint point) {
	CMyShape::offset(point);
	POSITION pos = m_pts.GetHeadPosition();
	while (pos) {
		m_pts.GetNext(pos).Offset(point);
	}
}