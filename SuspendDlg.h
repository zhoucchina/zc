#pragma once
#include "MyButton.h"
#include "afxwin.h"

// CSuspendDlg 对话框

class CSuspendDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSuspendDlg)

public:
	CSuspendDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSuspendDlg();
	COLORREF  m_DlgBkColor;

// 对话框数据
	enum { IDD = IDD_SUSPEND_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton20();
	
	CString m_strSet;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton19();
};
