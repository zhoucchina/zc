#pragma once

class CMyButton : public CButton
{
public:
	CMyButton();
	virtual ~CMyButton();
	//����Button Down�ı�����ɫ
	void SetDownColor(COLORREF color);
	//����Button Up�ı�����ɫ
	void SetUpColor(COLORREF color);
	BOOL Attach(const UINT nID, CWnd* pParent);
	bool m_bMouseOn;
protected:
	//�������صĺ���
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

public:
	//������ɫ�ֱ�Ϊ���֣�Button Down�ı�����ɫ��Button Up�ı�����ɫ
	COLORREF m_TextColor, m_DownColor, m_UpColor;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
//	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
};


