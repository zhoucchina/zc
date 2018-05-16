// MyButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyButton.h"
#include "resource.h"

CMyButton::CMyButton(void)
{
	m_DownColor = m_UpColor = RGB(0,0,0);
	m_bMouseOn = false;
}
CMyButton::~CMyButton(void)
{
}

//CMyButton��CButton�����࣬����CButton��ȫ����Ա������
//���ڴ���ʱ��Ҫʹ��BS_OWNERDRAW���
//�����ť���Ƕ�̬���ɣ�ʹ��Attach����ʹCMyButton����ԭ����ť�Ĵ��ڹ��̡�
BOOL CMyButton::Attach(const UINT nID, CWnd* pParent)
{
	//GetDlgItem(nID)->ModifyStyle(0,BS_OWNERDRAW,0);
	if (!SubclassDlgItem(nID, pParent))
		return FALSE;
	return TRUE;
}
void CMyButton::SetDownColor(COLORREF color)
{
	m_DownColor = color;
}
void CMyButton::SetUpColor(COLORREF color)
{
	m_UpColor = color;
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your code to draw the specified item
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);//�õ����Ƶ��豸����CDC
	VERIFY(lpDrawItemStruct->CtlType==ODT_BUTTON);

	// �õ�Button������,����Ĳ�����:1,�ȵõ�����Դ��༭�İ�ť������,
	//Ȼ�󽫴��������»��Ƶ���ť��,
	//ͬʱ�������ֵı���ɫ��Ϊ͸��,����,��ť�Ͻ�����ʾ����
	const int bufSize = 512;
	TCHAR buffer[bufSize];
	GetWindowText(buffer, bufSize);
	int size=lstrlen(buffer);   //�õ�����
	DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);   //��������
	SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);   //͸��
	//dc.SetTextColor(RGB(255,255,0));

	CBrush brush(m_UpColor); 

	CRect rc(lpDrawItemStruct->rcItem);
	
	/*dc.BeginPath();
	dc.MoveTo(rc.Height()/2,rc.Height()/2);
	dc.AngleArc(rc.Height()/2,rc.Height()/2,rc.Height()/2,90,180);

	dc.LineTo(rc.Width()-rc.Height()/2,rc.Height());
	dc.AngleArc(rc.Width()-rc.Height()/2,rc.Height()/2,rc.Height()/2,270,180);

	dc.LineTo(rc.Height()/2,0);
	dc.EndPath();
	CRgn rgn;
	rgn.CreateFromPath(&dc);
	dc.FillRgn(&rgn,&brush);*/
	
	dc.FillRect(&(lpDrawItemStruct->rcItem),&brush);//
	//��Ϊ����������ػ�,��������ҲҪ�ػ�

	if (lpDrawItemStruct->itemState &ODS_SELECTED)  //�����°�ťʱ�Ĵ���
	{//
		CBrush brush(m_DownColor);  
		dc.FillRect(&(lpDrawItemStruct->rcItem),&brush);

		dc.SetTextColor(RGB(0,0,255));
		
		DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);  
		SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);

	}
	else if (m_bMouseOn)  //�����°�ťʱ�Ĵ���
	{//

		dc.SetTextColor(RGB(0,255,255));

		DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);  
		SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);      
	}
	else                       //����ť���������ߵ���ʱ
	{		
		
		dc.SetTextColor(RGB(150,150,150));
		DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);    
		SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);
	}
	
	dc.Detach();//
}
BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
//	ON_WM_MOUSEHOVER()
END_MESSAGE_MAP()


void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	
	if(!m_bMouseOn)
	{
		TRACKMOUSEEVENT   tme;  
		tme.cbSize = sizeof(TRACKMOUSEEVENT);  
		tme.dwFlags = TME_HOVER | TME_LEAVE;  
		tme.dwHoverTime = HOVER_DEFAULT;  
		tme.hwndTrack = m_hWnd;  
		_TrackMouseEvent(&tme);  

		m_bMouseOn = true;
		Invalidate(FALSE);
	}
	
	CButton::OnMouseMove(nFlags, point);
}


void CMyButton::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	if(m_bMouseOn)
	{
		m_bMouseOn = false;
		Invalidate(FALSE);
	}
	
	CButton::OnMouseLeave();
}

