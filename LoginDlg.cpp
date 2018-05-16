// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON20, &CLoginDlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON18, &CLoginDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CLoginDlg::OnBnClickedButton19)
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_DlgBkColor = RGB(100,100,100);

	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|WS_EX_LAYERED);
	SetLayeredWindowAttributes(0,255,LWA_ALPHA);
	SetBackgroundColor(m_DlgBkColor);

	/*DWORD dwStyle= GetWindowLong(m_hotKey.m_hWnd, GWL_STYLE); 
	SetWindowLong( m_hotKey.m_hWnd, GWL_STYLE, dwStyle  |BS_AUTOCHECKBOX );*/
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	pBtn->SetCheck(1);

	CWnd   *pWnd; 


	pWnd=GetWindow(GW_CHILD); 
	while   (pWnd!=NULL) 
	{ 
		TCHAR ClassName[129];
		GetClassName(pWnd->m_hWnd, ClassName, 128); 
		if( _tcsicmp( ClassName, _T("Button")) == 0)
		{
			int ID = pWnd->GetDlgCtrlID();
			if(IDC_CHECK1 == ID)
			{
				pWnd=pWnd-> GetNextWindow(); 
				continue;
			}
			CMyButton* bt = new CMyButton;
			GetDlgItem(ID)->ModifyStyle(0,BS_OWNERDRAW,0);
			//�󶨿ؼ�IDC_BUTTON1����CMyButton����Ӧ���غ���DrawItem()
			bt->Attach(ID,this);
			//����Button Down�ı���ɫ
			bt->SetDownColor(RGB(255,0,0));
			//����Button Up�ı���ɫ
			bt->SetUpColor(RGB(255,255,0));
		}

		pWnd=pWnd-> GetNextWindow(); 
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CLoginDlg::OnBnClickedButton1()
{
	//�رհ�ť
	CDialog::OnOK();
}


void CLoginDlg::OnBnClickedButton20()
{
	// QQ��¼
	CDialog::OnOK();
}


void CLoginDlg::OnBnClickedButton2()
{
	// ������¼

	CDialog::OnOK();

}


HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	//if(nCtlColor == CTLCOLOR_EDIT )
	//{
	//	//pDC->SetBkMode(TRANSPARENT);   
	//	pDC->SetBkColor(RGB(200,200,200));  
	//	return   (HBRUSH)::GetStockObject(NULL_BRUSH);   
	//}

	return hbr;
}


void CLoginDlg::OnBnClickedButton18()
{
	
}


void CLoginDlg::OnBnClickedButton19()
{
	
}
