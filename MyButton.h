#pragma once

class CMyButton : public CButton
{
public:
	CMyButton();
	virtual ~CMyButton();
	//设置Button Down的背景颜色
	void SetDownColor(COLORREF color);
	//设置Button Up的背景颜色
	void SetUpColor(COLORREF color);
	BOOL Attach(const UINT nID, CWnd* pParent);
	bool m_bMouseOn;
protected:
	//必需重载的函数
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

public:
	//三种颜色分别为文字，Button Down的背景颜色，Button Up的背景颜色
	COLORREF m_TextColor, m_DownColor, m_UpColor;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
//	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
};


