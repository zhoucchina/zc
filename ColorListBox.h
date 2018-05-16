#pragma once


// CColorListBox

class CColorListBox : public CListBox
{
public:
	CColorListBox();
	virtual ~CColorListBox();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	int AddString(LPCTSTR lpszItem, COLORREF itemColor = RGB(200,200,200));
	bool m_bMouseOn;
	int m_select;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};


