// ColorListBox.cpp : 实现文件
//

#include "stdafx.h"
#include "ColorListBox.h"


CColorListBox::CColorListBox()
{
	m_bMouseOn = false;
	
}

CColorListBox::~CColorListBox()
{
}


/********************************************************************/
/*																	*/
/* Function name : AddString										*/		
/* Description   : Add string to the listbox and save color info.	*/
/*																	*/
/********************************************************************/
int CColorListBox::AddString(LPCTSTR lpszItem, COLORREF itemColor)
{
	// Add the string to the list box
	int nIndex = CListBox::AddString(lpszItem);

	// save color data
	if (nIndex >= 0)
		SetItemData(nIndex, itemColor);

	return nIndex;
}


/********************************************************************/
/*																	*/
/* Function name : DrawItem											*/		
/* Description   : Called by the framework when a visual aspect of	*/
/*				   an owner-draw list box changes.					*/
/*																	*/
/********************************************************************/
void CColorListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// Losing focus ?
	if (lpDrawItemStruct->itemID == -1) 
	{
		DrawFocusRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem);
		return;
	}
	
	CString imgPath[] = {"res\\侧边栏\\首页.png","res\\侧边栏\\收藏.png","res\\侧边栏\\本地导入.png",
		                 "res\\侧边栏\\钱包.png"};
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	
	COLORREF clrOld;
	CString sText;

	
	

	// get color info from item data
	COLORREF clrNew = (COLORREF)(lpDrawItemStruct->itemData);
	// set the background mode to TRANSPARENT
	
	int nBkMode = pDC->SetBkMode(TRANSPARENT);
	
	lpDrawItemStruct->rcItem.top += 10;
	lpDrawItemStruct->rcItem.bottom -= 10;


	// item selected ?
	if ((lpDrawItemStruct->itemState & ODS_SELECTED) &&
		(lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		CBrush brush(RGB(50,50,50));
		pDC->FillRect(&lpDrawItemStruct->rcItem, &brush);

		//memdc.SetBkColor(RGB(100, 100, 100));
		//pDC->BitBlt(rc.left, rc.top+5,30,30, &memdc, 0, 0,SRCAND); 

	}

	// item deselected ?
	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) &&	
		(lpDrawItemStruct->itemAction & ODA_SELECT))
	{
		CBrush brush(::GetSysColor(COLOR_WINDOW));
		pDC->FillRect(&lpDrawItemStruct->rcItem, &brush);


	}	 	

	// item has focus ?
	if ((lpDrawItemStruct->itemAction & ODA_FOCUS) && 
		(lpDrawItemStruct->itemState & ODS_FOCUS))
	{
		//pDC->DrawFocusRect(&lpDrawItemStruct->rcItem); 
	}

	// lost focus ?
	if ((lpDrawItemStruct->itemAction & ODA_FOCUS) &&	
		!(lpDrawItemStruct->itemState & ODS_FOCUS))
	{
		//pDC->DrawFocusRect(&lpDrawItemStruct->rcItem); 
	}

	

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		clrOld = pDC->SetTextColor(clrNew);
	}
	else 
	{
		if (lpDrawItemStruct->itemState & ODS_DISABLED)
			clrOld = pDC->SetTextColor(clrNew);
		else if(m_bMouseOn && lpDrawItemStruct->itemID == m_select)
		{
			//clrOld = pDC->SetTextColor(RGB(0,255,255));
			CBrush brush(::GetSysColor(COLOR_WINDOW));
			pDC->FillRect(&lpDrawItemStruct->rcItem, &brush);

		}
		else
		{
			clrOld = pDC->SetTextColor(clrNew);
			CBrush brush(RGB(100,100,100));
			pDC->FillRect(&lpDrawItemStruct->rcItem, &brush);
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
	//memdc.SetBkColor(RGB(255, 255, 255));
	//pDC->BitBlt(rc.left, rc.top+5,30,30, &memdc, 0, 0,SRCAND); 


	//clrOld = pDC->SetTextColor(clrNew);
	// get item text
	GetText(lpDrawItemStruct->itemID, sText);
	CRect rect = lpDrawItemStruct->rcItem;
	rect.left  += 30;
	// text format
	UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER;
	if (GetStyle() & LBS_USETABSTOPS)
		nFormat |= DT_EXPANDTABS;

	// draw the text
	pDC->DrawText(sText, -1, &rect, nFormat);



	// restore old values
	pDC->SetTextColor(clrOld); 
	pDC->SetBkMode(nBkMode);
}


void CColorListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	lpMeasureItemStruct->itemHeight = 50;	
}

// CColorListBox 消息处理程序


BEGIN_MESSAGE_MAP(CColorListBox, CListBox)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


void CColorListBox::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
		TRACKMOUSEEVENT   tme;  
		tme.cbSize = sizeof(TRACKMOUSEEVENT);  
		tme.dwFlags = TME_HOVER | TME_LEAVE;  
		tme.dwHoverTime = HOVER_DEFAULT;  
		tme.hwndTrack = m_hWnd;  
		_TrackMouseEvent(&tme);  

		int nCount = GetCount();
		for (int i = 0; i <nCount; i++)
		{
			CRect rc;

			this->GetItemRect(i,&rc);
			if(rc.PtInRect(point) && m_select != i)
			{
				m_select = i;
				break;
			}
		}

		m_bMouseOn = true;
		//Invalidate(FALSE);
	
	CListBox::OnMouseMove(nFlags, point);
}


void CColorListBox::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bMouseOn)
	{
		m_bMouseOn = false;
		//Invalidate(FALSE);
	}

	CListBox::OnMouseLeave();
}
