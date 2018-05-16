// MyListCtrl.cpp : 实现文件
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



// CMyListCtrl 消息处理程序


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

	CString imgPath[] = {"res\\侧边栏\\首页.png","res\\侧边栏\\收藏.png","res\\侧边栏\\本地导入.png",
		"res\\侧边栏\\钱包.png"};

	//高亮显示    
	BOOL bHighlight =((lvi.state & LVIS_DROPHILITED)||((lvi.state & LVIS_SELECTED)   
		&& ((GetFocus() == this)|| (GetStyle() & LVS_SHOWSELALWAYS))));  

	//画文本背景   
	CRect rcBack = lpDrawItemStruct->rcItem;   
	 pDC->SetBkMode(TRANSPARENT);   

	


	if( bHighlight ) //如果被选中  
	{   
		pDC->SetTextColor(RGB(255,255,255));              //文本颜色  
	    pDC->FillRect(rcBack, &CBrush(RGB(90,162,100)));  //行背景色  
	}   
	else   
	{   
		int iRow = lvi.iItem;  
		/*if(iRow % 2 == 0)  
		{  */
			pDC->SetTextColor(RGB(0,0,0));                    //文本颜色  
			pDC->FillRect(rcBack, &CBrush(RGB(211,223,238))); //行背景色  
		//}  
	}   

	//绘制文本  
	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)   
	{   
		//得到列数  
		int nCollumn = GetHeaderCtrl()->GetItemCount();  

		//循环处理  
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