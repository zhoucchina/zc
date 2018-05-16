#pragma once
#include "LoginDlg.h"
#include "RegDlg.h"

// CLoginRegDlg 对话框

class CLoginRegDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginRegDlg)

public:
	CLoginRegDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginRegDlg();
	CLoginDlg  m_loginDlg;
	CRegDlg    m_regDlg;
	COLORREF   m_DlgBkColor;
// 对话框数据
	enum { IDD = IDD_LOGIN_REG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton1();
};
