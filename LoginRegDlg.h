#pragma once
#include "LoginDlg.h"
#include "RegDlg.h"

// CLoginRegDlg �Ի���

class CLoginRegDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginRegDlg)

public:
	CLoginRegDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginRegDlg();
	CLoginDlg  m_loginDlg;
	CRegDlg    m_regDlg;
	COLORREF   m_DlgBkColor;
// �Ի�������
	enum { IDD = IDD_LOGIN_REG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton1();
};
