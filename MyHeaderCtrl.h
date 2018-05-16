#pragma once


// CMyHeaderCtrl

class CMyHeaderCtrl : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CMyHeaderCtrl)

public:
	CMyHeaderCtrl();
	virtual ~CMyHeaderCtrl();

protected:
	//LRESULT OnLayout( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()
};


