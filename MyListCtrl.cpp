// MyListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "MyListCtrl.h"


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)

CMyListCtrl::CMyListCtrl()
{

}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//ON_WM_MEASUREITEM()
	//ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM_REFLECT()
END_MESSAGE_MAP()



// CMyListCtrl ��Ϣ�������


void CMyListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)  
{  
	//CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);  
	lpMeasureItemStruct->itemHeight = 50;
}  

void CMyListCtrl::SetRowHeigt(int nHeight)  
{  
	m_nRowHeight = nHeight;  

	CRect rcWin;  
	GetWindowRect(&rcWin);  
	WINDOWPOS wp;  
	wp.hwnd = m_hWnd;  
	wp.cx = rcWin.Width();  
	wp.cy = rcWin.Height();  
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;  
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);  
}  

void CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)  
{  

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);      
	LVITEM lvi = {0};   
	lvi.mask = LVIF_STATE;//|LVIF_IMAGE;   
	lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED ;   
	lvi.iItem = lpDrawItemStruct->itemID;   
	BOOL bGet = GetItem(&lvi);   

	CString imgPath[] = {"res\\�����\\��ҳ.png","res\\�����\\�ղ�.png","res\\�����\\���ص���.png",
		"res\\�����\\Ǯ��.png"};

	//������ʾ    
	BOOL bHighlight =((lvi.state & LVIS_DROPHILITED)||((lvi.state & LVIS_SELECTED)   
		&& ((GetFocus() == this)|| (GetStyle() & LVS_SHOWSELALWAYS))));  

	//���ı�����   
	CRect rcBack = lpDrawItemStruct->rcItem;   
	 pDC->SetBkMode(TRANSPARENT);   

	


	if( bHighlight ) //�����ѡ��  
	{   
		pDC->SetTextColor(RGB(255,255,255));              //�ı���ɫ  
	    pDC->FillRect(rcBack, &CBrush(RGB(90,162,100)));  //�б���ɫ  
	}   
	else   
	{   
		int iRow = lvi.iItem;  
		/*if(iRow % 2 == 0)  
		{  */
			pDC->SetTextColor(RGB(0,0,0));                    //�ı���ɫ  
			pDC->FillRect(rcBack, &CBrush(RGB(211,223,238))); //�б���ɫ  
		//}  
	}   

	//�����ı�  
	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)   
	{   
		//�õ�����  
		int nCollumn = GetHeaderCtrl()->GetItemCount();  

		//ѭ������  
		CString szText;   
		for (int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)   
		{    
			CRect rcItem;   
			if ( !GetSubItemRect(lpDrawItemStruct->itemID, i, LVIR_LABEL, rcItem ))  
			{   
				continue;   
			}  

			szText = GetItemText( lpDrawItemStruct->itemID, i );  

			rcItem.left += 5; rcItem.right -= 1;   
			pDC->DrawText(szText, lstrlen(szText), &rcItem,    
				DT_LEFT | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);    
		}   
	} 


	CImage img;
	CRect rc(lpDrawItemStruct->rcItem);
	img.Load(imgPath[0]);
	HBITMAP hbitmap = img.Detach();
	CBitmap cBitmap;
	BITMAP bitmap;
	CDC memdc;
	cBitmap.Attach(hbitmap);
	memdc.CreateCompatibleDC(pDC);
	memdc.SelectObject(hbitmap);
	cBitmap.GetBitmap(&bitmap); 
	pDC->TransparentBlt(rc.left, rc.top+5,24,24, &memdc, 0, 0, 24, 24,RGB(255,255,255)); 



} 