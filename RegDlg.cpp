// RegDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "RegDlg.h"
#include "afxdialogex.h"
#include "MyButton.h"

// CRegDlg 对话框

IMPLEMENT_DYNAMIC(CRegDlg, CDialogEx)

CRegDlg::CRegDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegDlg::IDD, pParent)
{

}

CRegDlg::~CRegDlg()
{
}

void CRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CRegDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CRegDlg 消息处理程序


void CRegDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CRegDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_DlgBkColor = RGB(100,100,100);

	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|WS_EX_LAYERED);
	SetLayeredWindowAttributes(0,255,LWA_ALPHA);
	SetBackgroundColor(m_DlgBkColor);

	/*DWORD dwStyle= GetWindowLong(m_hotKey.m_hWnd, GWL_STYLE); 
	SetWindowLong( m_hotKey.m_hWnd, GWL_STYLE, dwStyle  |BS_AUTOCHECKBOX );*/
	CWnd   *pWnd; 
	pWnd=GetWindow(GW_CHILD); 
	while   (pWnd!=NULL) 
	{ 
		TCHAR ClassName[129];
		GetClassName(pWnd->m_hWnd, ClassName, 128); 
		if( _tcsicmp( ClassName, _T("Button")) == 0)
		{
			int ID = pWnd->GetDlgCtrlID();
			CMyButton* bt = new CMyButton;
			GetDlgItem(ID)->ModifyStyle(0,BS_OWNERDRAW,0);
			//绑定控件IDC_BUTTON1与类CMyButton，响应重载函数DrawItem()
			bt->Attach(ID,this);
			//设置Button Down的背景色
			bt->SetDownColor(RGB(255,0,0));
			//设置Button Up的背景色
			bt->SetUpColor(RGB(255,255,0));
		}

		pWnd=pWnd-> GetNextWindow(); 
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
