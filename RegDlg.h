#pragma once


// CRegDlg �Ի���

class CRegDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegDlg)

public:
	CRegDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegDlg();
	COLORREF  m_DlgBkColor;
// �Ի�������
	enum { IDD = IDD_REG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
};
