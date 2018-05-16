#pragma once


// CMyListCtrl

class CMyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)

public:
	CMyListCtrl();
	virtual ~CMyListCtrl();
	virtual  void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) ;

	void SetRowHeigt(int nHeight);	
	int m_nRowHeight;

protected:
	DECLARE_MESSAGE_MAP()
};


