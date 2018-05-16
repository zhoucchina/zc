// SuspendDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "SuspendDlg.h"
#include "afxdialogex.h"


// CSuspendDlg �Ի���

IMPLEMENT_DYNAMIC(CSuspendDlg, CDialogEx)

CSuspendDlg::CSuspendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSuspendDlg::IDD, pParent)
	, m_strSet(_T(""))
{

}

CSuspendDlg::~CSuspendDlg()
{
}

void CSuspendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_strSet);
}


BEGIN_MESSAGE_MAP(CSuspendDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON20, &CSuspendDlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON1, &CSuspendDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON19, &CSuspendDlg::OnBnClickedButton19)
END_MESSAGE_MAP()


// CSuspendDlg ��Ϣ�������


BOOL CSuspendDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_DlgBkColor = RGB(100,100,100);

	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|WS_EX_LAYERED);
	SetLayeredWindowAttributes(0,200,LWA_ALPHA);
	SetBackgroundColor(m_DlgBkColor);

	/*DWORD dwStyle= GetWindowLong(m_hotKey.m_hWnd, GWL_STYLE); 
	SetWindowLong( m_hotKey.m_hWnd, GWL_STYLE, dwStyle  |BS_AUTOCHECKBOX );*/
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	pBtn->SetCheck(1);

	m_strSet = "CTRL+ATL+F5";
	UpdateData(false);
		

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
			bt->SetDownColor(m_DlgBkColor);
			//����Button Up�ı���ɫ
			bt->SetUpColor(m_DlgBkColor);
		}

		pWnd=pWnd-> GetNextWindow(); 
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CSuspendDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor == CTLCOLOR_EDIT )
	{
		pDC->SetBkMode(TRANSPARENT);   
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);   
	}
	
	return hbr;
}


void CSuspendDlg::OnBnClickedButton20()
{
	//�رհ�ť
	 CDialog::OnOK();
}


void CSuspendDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 CDialog::OnOK();
}


void CSuspendDlg::OnBnClickedButton19()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 CDialog::OnCancel();
}
