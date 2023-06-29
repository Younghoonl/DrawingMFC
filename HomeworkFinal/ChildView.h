
// ChildView.h : interface of the CChildView class
//


#pragma once

#include "CMyShape.h"
#include "CMyCircle.h"
#include "CMyCurve.h"
#include "CMyRect.h"
#include "CMyStar.h"
#include "CMyGroup.h"

// CChildView window

class CChildView : public CWnd
{
	// Construction
public:
	CChildView();

	// Attributes
public:
	enum Action {
		rectangle, circle, curve, star, select
	} m_action;
	CList<CMyShape*> m_shapes;
	CList<CMyShape*> m_selected;
	CPoint m_selectStart, m_selectEnd;
	bool m_selectDrag;

	// Operations
public:

	// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDrawRectangle();
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawCurve();
	afx_msg void OnDrawStar();
	afx_msg void OnUpdateDrawRectangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawCurve(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawStar(CCmdUI* pCmdUI);
	afx_msg void OnActionSelect();
	afx_msg void OnUpdateActionSelect(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnAlignBringfront();
	afx_msg void OnUpdateAlignBringfront(CCmdUI* pCmdUI);
	afx_msg void OnAlignBringback();
	afx_msg void OnUpdateAlignBringback(CCmdUI* pCmdUI);
	afx_msg void OnActionGroup();
	afx_msg void OnUpdateActionGroup(CCmdUI* pCmdUI);
	afx_msg void OnActionUngroup();
	afx_msg void OnUpdateActionUngroup(CCmdUI* pCmdUI);
};

