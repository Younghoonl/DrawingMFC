
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "homeworkFinal.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView() : m_action(Action::rectangle), m_selectDrag(false)
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DRAW_RECTANGLE, &CChildView::OnDrawRectangle)
	ON_COMMAND(ID_DRAW_CIRCLE, &CChildView::OnDrawCircle)
	ON_COMMAND(ID_DRAW_CURVE, &CChildView::OnDrawCurve)
	ON_COMMAND(ID_DRAW_STAR, &CChildView::OnDrawStar)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECTANGLE, &CChildView::OnUpdateDrawRectangle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CChildView::OnUpdateDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CURVE, &CChildView::OnUpdateDrawCurve)
	ON_UPDATE_COMMAND_UI(ID_DRAW_STAR, &CChildView::OnUpdateDrawStar)
	ON_COMMAND(ID_ACTION_SELECT, &CChildView::OnActionSelect)
	ON_UPDATE_COMMAND_UI(ID_ACTION_SELECT, &CChildView::OnUpdateActionSelect)
	ON_WM_KEYDOWN()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ALIGN_BRINGFRONT, &CChildView::OnAlignBringfront)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_BRINGFRONT, &CChildView::OnUpdateAlignBringfront)
	ON_COMMAND(ID_ALIGN_BRINGBACK, &CChildView::OnAlignBringback)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_BRINGBACK, &CChildView::OnUpdateAlignBringback)
	ON_COMMAND(ID_ACTION_GROUP, &CChildView::OnActionGroup)
	ON_UPDATE_COMMAND_UI(ID_ACTION_GROUP, &CChildView::OnUpdateActionGroup)
	ON_COMMAND(ID_ACTION_UNGROUP, &CChildView::OnActionUngroup)
	ON_UPDATE_COMMAND_UI(ID_ACTION_UNGROUP, &CChildView::OnUpdateActionUngroup)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(rect);
	int w = rect.Width();
	int h = rect.Height();

	CDC offDc;
	offDc.CreateCompatibleDC(&dc);
	CBitmap offBmp;
	offBmp.CreateCompatibleBitmap(&dc, w, h);
	offDc.SelectObject(offBmp);
	offDc.SelectStockObject(NULL_PEN);
	offDc.Rectangle(rect);
	offDc.SetBkMode(TRANSPARENT);

	POSITION pos = m_shapes.GetHeadPosition();
	POSITION posSelected = m_selected.GetHeadPosition();
	while (pos) {
		CMyShape* u = m_shapes.GetNext(pos);
		u->draw(offDc);
		if (posSelected) {
			CMyShape* v = m_selected.GetAt(posSelected);
			if (u == v) {
				CPen pen(PS_DOT, 1, RGB(255, 0, 0));
				offDc.SelectObject(pen);
				offDc.SelectStockObject(NULL_BRUSH);
				CRect rect = u->getBbox();
				rect.InflateRect(5, 5);
				offDc.Rectangle(rect);
				m_selected.GetNext(posSelected);
			}
		}
	}

	if (m_action == select && m_selectDrag) {
		CPen pen(PS_DOT, 1, RGB(0, 0, 0));
		offDc.SelectObject(pen);
		offDc.SelectStockObject(NULL_BRUSH);
		offDc.Rectangle(CRect(m_selectStart, m_selectEnd));
	}

	CString information_string = _T("");
	information_string.AppendFormat(_T("Number of Shapes: %zd\r\n"), m_shapes.GetSize());
	information_string.AppendFormat(_T("Number of Selected: %zd\r\n"), m_selected.GetSize());
	offDc.DrawText(information_string, rect, DT_LEFT | DT_TOP);

	dc.BitBlt(0, 0, w, h, &offDc, 0, 0, SRCCOPY);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	return CWnd::OnEraseBkgnd(pDC);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	switch (m_action) {
	case rectangle: m_shapes.AddTail(new CMyRect(point)); break;
	case circle: m_shapes.AddTail(new CMyCircle(point)); break;
	case curve: m_shapes.AddTail(new CMyCurve(point)); break;
	case star: m_shapes.AddTail(new CMyStar(point)); break;
	case select:
		m_selectStart = m_selectEnd = point;
		if (~nFlags & MK_SHIFT) {
			m_selected.RemoveAll();
		}
		POSITION pos = m_shapes.GetTailPosition();
		POSITION posSelected = m_selected.GetTailPosition();
		m_selectDrag = true;
		while (pos) {
			CMyShape* u = m_shapes.GetPrev(pos);
			if (u->pointCollision(point)) {
				m_selectDrag = false;
				if (posSelected) {
					CMyShape* v = m_selected.GetAt(posSelected);
					if (u == v) {
						break;
					}
				}
				if (posSelected) {
					m_selected.InsertAfter(posSelected, u);
				}
				else {
					m_selected.AddHead(u);
				}
				break;
			}
			if (posSelected) {
				CMyShape* v = m_selected.GetAt(posSelected);
				if (u == v) {
					m_selected.GetPrev(posSelected);
				}
			}
		}
		break;
	}
	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON) {
		if (m_action == select && m_selectDrag) {
			m_selectEnd = point;
		}
		else if (m_action == select && !m_selectDrag) {
			POSITION pos = m_selected.GetHeadPosition();
			CPoint dPoint = point - m_selectEnd;
			while (pos) {
				CMyShape* u = m_shapes.GetNext(pos);
				u->offset(dPoint);
			}
			m_selectEnd = point;
		}
		else {
			m_shapes.GetTail()->update(point);
		}
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	if (m_action == select && m_selectDrag) {
		POSITION pos = m_shapes.GetTailPosition();
		POSITION posSelected = m_selected.GetTailPosition();
		while (pos) {
			CMyShape* u = m_shapes.GetPrev(pos);
			if (posSelected) {
				CMyShape* v = m_selected.GetAt(posSelected);
				if (u == v) {
					m_selected.GetPrev(posSelected);
					continue;
				}
			}
			if (u->rectCollision(CRect(m_selectStart, m_selectEnd))) {
				if (posSelected) {
					CMyShape* v = m_selected.GetAt(posSelected);
					if (u == v) {
						continue;
					}
				}
				if (posSelected) {
					m_selected.InsertAfter(posSelected, u);
				}
				else {
					m_selected.AddHead(u);
				}
			}
		}
		m_selectStart = m_selectEnd;
		Invalidate();
	}
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnDrawRectangle()
{
	m_action = rectangle;
	m_selected.RemoveAll();
	Invalidate();
}


void CChildView::OnDrawCircle()
{
	m_action = circle;
	m_selected.RemoveAll();
	Invalidate();
}


void CChildView::OnDrawCurve()
{
	m_action = curve;
	m_selected.RemoveAll();
	Invalidate();
}


void CChildView::OnDrawStar()
{
	m_action = star;
	m_selected.RemoveAll();
	Invalidate();
}


void CChildView::OnUpdateDrawRectangle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_action == rectangle);
}


void CChildView::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_action == circle);
}


void CChildView::OnUpdateDrawCurve(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_action == curve);
}


void CChildView::OnUpdateDrawStar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_action == star);
}


void CChildView::OnActionSelect()
{
	m_action = select;
}


void CChildView::OnUpdateActionSelect(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_action == select);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DELETE) {
		POSITION pos = m_shapes.GetHeadPosition();
		POSITION posSelected = m_selected.GetHeadPosition();
		while (posSelected) {
			CMyShape* u = m_shapes.GetAt(pos);
			CMyShape* v = m_selected.GetAt(posSelected);
			if (u == v) {
				POSITION removePos = pos;
				m_shapes.GetNext(pos);
				m_selected.GetNext(posSelected);
				m_shapes.RemoveAt(removePos);
				delete u;
				continue;
			}
			m_shapes.GetNext(pos);
		}
		m_selected.RemoveAll();
		Invalidate();
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);

	CMenu* pMenu = menu.GetSubMenu(3);

	pMenu->TrackPopupMenu(
		TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, AfxGetMainWnd());
}


void CChildView::OnAlignBringfront()
{
	POSITION pos = m_shapes.GetHeadPosition();
	POSITION posSelected = m_selected.GetHeadPosition();
	INT_PTR size = m_shapes.GetSize();
	for (int i = 0; i < size; ++i) {
		CMyShape* u = m_shapes.GetAt(pos);
		CMyShape* v = m_selected.GetAt(posSelected);
		if (u == v) {
			POSITION removePos = pos;
			POSITION removePosSelected = posSelected;
			m_shapes.AddTail(u);
			m_selected.AddTail(v);
			m_shapes.GetNext(pos);
			m_selected.GetNext(posSelected);
			m_shapes.RemoveAt(removePos);
			m_selected.RemoveAt(removePosSelected);
		}
		else
		m_shapes.GetNext(pos);
	}
	Invalidate();
}


void CChildView::OnUpdateAlignBringfront(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!m_selected.IsEmpty());
}


void CChildView::OnAlignBringback()
{
	POSITION pos = m_shapes.GetTailPosition();
	POSITION posSelected = m_selected.GetTailPosition();
	INT_PTR size = m_shapes.GetSize();
	for (int i = 0; i < size; ++i) {
		CMyShape* u = m_shapes.GetAt(pos);
		CMyShape* v = m_selected.GetAt(posSelected);
		if (u == v) {
			POSITION removePos = pos;
			POSITION removePosSelected = posSelected;
			m_shapes.AddHead(u);
			m_selected.AddHead(v);
			m_shapes.GetPrev(pos);
			m_selected.GetPrev(posSelected);
			m_shapes.RemoveAt(removePos);
			m_selected.RemoveAt(removePosSelected);
		}
		else
			m_shapes.GetPrev(pos);
	}
	Invalidate();
}


void CChildView::OnUpdateAlignBringback(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!m_selected.IsEmpty());
}


void CChildView::OnActionGroup()
{
	m_shapes.AddTail(new CMyGroup(m_selected));
	POSITION pos = m_shapes.GetHeadPosition();
	POSITION posSelected = m_selected.GetHeadPosition();
	while (posSelected) {
		CMyShape* u = m_shapes.GetAt(pos);
		CMyShape* v = m_selected.GetAt(posSelected);
		if (u == v) {
			POSITION removePos = pos;
			m_shapes.GetNext(pos);
			m_selected.GetNext(posSelected);
			m_shapes.RemoveAt(removePos);
			continue;
		}
		m_shapes.GetNext(pos);
	}
	m_selected.RemoveAll();
	m_selected.AddTail(m_shapes.GetTail());
	Invalidate();
}


void CChildView::OnUpdateActionGroup(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_selected.GetSize() >= 2);
}


void CChildView::OnActionUngroup()
{
	POSITION pos = m_shapes.GetHeadPosition();
	POSITION posSelected = m_selected.GetHeadPosition();
	INT_PTR size = m_shapes.GetSize();
	for (int i = 0; i < size; ++i) {
		CMyShape* u = m_shapes.GetAt(pos);
		CMyShape* v = m_selected.GetAt(posSelected);
		if (u == v) {
			POSITION removePos = pos;
			POSITION removePosSelected = posSelected;
			CList<CMyShape*> children;
			u->ungroup(children);
			m_shapes.AddTail(&children);
			m_selected.AddTail(&children);
			m_shapes.GetNext(pos);
			m_selected.GetNext(posSelected);
			if (children.IsEmpty()) continue;
			m_shapes.RemoveAt(removePos);
			m_selected.RemoveAt(removePosSelected);
			delete u;
		}
		else
			m_shapes.GetNext(pos);
	}
	Invalidate();
}


void CChildView::OnUpdateActionUngroup(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!m_selected.IsEmpty());
}
