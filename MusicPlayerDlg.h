
// MusicPlayerDlg.h : 头文件
//

#pragma once
#include <mmsystem.h>
#include "afxcmn.h"
#include "afxwin.h"
#include <string>
#include <vector>
#include <algorithm>
#include "MyButton.h"
#include "ColorListBox.h"
#include "MyListCtrl.h"
#include <SETUPAPI.H>         
#include <rpcdce.h>  

//#include <SHLWAPI.H>     
   #pragma comment(lib, "Rpcrt4.lib") 
//#pragma comment(lib, "shlwapi.lib")  
#pragma comment(lib, "setupapi.lib")     
#pragma comment(lib, "winmm.lib")
using namespace std;

// CMusicPlayerDlg 对话框

class CMusicPlayerDlg : public CDialogEx
{
// 构造
public:
	CMusicPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数
	DWORD getinfo(UINT wDeviceID,DWORD item);
	BOOL SetMicrPhoneVolume(DWORD dwVolume);
	void UpdateList(void);
	BOOL ChangeStatus(DWORD NewStatus, DWORD SelectedItem, HDEVINFO hDevInfo);
	BOOL ControlDisk(int nStatus);
	void ShowPic();

	MCI_OPEN_PARMS op;
	HMIXER  m_hMixer;
	CSliderCtrl m_slider;
	CStatic m_vol;
	CListCtrl m_listFile;

	CImageList m_ImgList;
	UINT       m_uImgID[5];

	string  m_fileName;
	UINT    m_fileIndex;
	CStatic* m_pPic[3];
	HBITMAP m_hBmp[3];
	

	UINT    m_indexPic;

	CMyButton  m_cbBtn;
	COLORREF  m_DlgBkColor;
	COLORREF  m_LstCtrlBkColor;
	COLORREF  m_LstBoxlBkColor;
	CColorListBox  m_ListBox;
	vector<string> m_musicVector;
// 对话框数据
	enum { IDD = IDD_MUSICPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	

// 实现
protected:
	HICON m_hIcon;
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPlayMic();
	afx_msg void OnStop();
	afx_msg void OnPause();	
	afx_msg void OnOpenMusicFile();	
	afx_msg void OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDel();		
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMCustomdrawList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLbnSelchangeList4();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton13();
};
