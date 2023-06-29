#include "pch.h"
#include "CMyGroup.h"

CMyGroup::CMyGroup(const CList<CMyShape*>& children) : CMyShape(CPoint(0, 0)) {
	POSITION pos = children.GetHeadPosition();
	while (pos) {
		m_children.AddTail(children.GetNext(pos));
	}
}


void CMyGroup::draw(CDC& dc) {
	POSITION pos = m_children.GetHeadPosition();
	while (pos) {
		m_children.GetNext(pos)->draw(dc);
	}
}


void CMyGroup::update(CPoint point) {
}


CRect CMyGroup::getBbox() {
	POSITION pos = m_children.GetHeadPosition();
	CRect rect = m_children.GetNext(pos)->getBbox();
	while (pos) {
		CRect r = m_children.GetNext(pos)->getBbox();
		rect.left = min(rect.left, r.left);
		rect.top = min(rect.top, r.top);
		rect.right = max(rect.right, r.right);
		rect.bottom = max(rect.bottom, r.bottom);
	}
	return rect;
}


bool CMyGroup::pointCollision(CPoint point) {
	POSITION pos = m_children.GetHeadPosition();
	while (pos) {
		if (m_children.GetNext(pos)->pointCollision(point)) {
			return true;
		}
	}
	return false;
}


void CMyGroup::offset(CPoint point) {
	POSITION pos = m_children.GetHeadPosition();
	while (pos) {
		m_children.GetNext(pos)->offset(point);
	}
}


void CMyGroup::ungroup(CList<CMyShape*>& children) {
	POSITION pos = m_children.GetHeadPosition();
	while (pos) {
		children.AddTail(m_children.GetNext(pos));
	}
}