// LoginRegDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "LoginRegDlg.h"
#include "afxdialogex.h"


// CLoginRegDlg 对话框

IMPLEMENT_DYNAMIC(CLoginRegDlg, CDialogEx)

CLoginRegDlg::CLoginRegDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginRegDlg::IDD, pParent)
{

}

CLoginRegDlg::~CLoginRegDlg()
{
}

void CLoginRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoginRegDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON18, &CLoginRegDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CLoginRegDlg::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginRegDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CLoginRegDlg 消息处理程序


BOOL CLoginRegDlg::OnInitDialog()
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





	CRect rc;
	GetClientRect(rc);
	rc.top += 80;


	m_loginDlg.Create(IDD_LOGIN_DLG,this);	
	m_loginDlg.MoveWindow(rc);
	m_loginDlg.ShowWindow(SW_SHOW);

	m_regDlg.Create(IDD_REG_DLG,this);	
	m_regDlg.MoveWindow(rc);
	m_regDlg.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CLoginRegDlg::OnBnClickedButton18()
{
	// 登录
	m_loginDlg.ShowWindow(SW_SHOW);
	m_regDlg.ShowWindow(SW_HIDE);
}


void CLoginRegDlg::OnBnClickedButton19()
{
	// 注册
	m_loginDlg.ShowWindow(SW_HIDE);
	m_regDlg.ShowWindow(SW_SHOW);
}


void CLoginRegDlg::OnBnClickedButton1()
{
	//关闭按钮
	CDialog::OnOK();
}
