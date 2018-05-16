
// MusicPlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "MusicPlayerDlg.h"
#include "SuspendDlg.h"
#include "LoginRegDlg.h"

#include "afxdialogex.h"
#include <mmdeviceapi.h>   
#include <endpointvolume.h>  
#include <audioclient.h>  
#include <winreg.h>
#include <devguid.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
long           DateLen;
bool           pauseFlag;
bool           stopFlag;
HANDLE         hSpeaker;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMusicPlayerDlg �Ի���




CMusicPlayerDlg::CMusicPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMusicPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_indexPic = 0;
}

void CMusicPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Control(pDX, IDC_STATIC1, m_vol);
	DDX_Control(pDX, IDC_LIST3, m_listFile);
	DDX_Control(pDX, IDC_LIST4, m_ListBox);
}

BEGIN_MESSAGE_MAP(CMusicPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CMusicPlayerDlg::OnPlayMic)
	ON_BN_CLICKED(IDC_BUTTON4, &CMusicPlayerDlg::OnStop)
	ON_BN_CLICKED(IDC_BUTTON2, &CMusicPlayerDlg::OnPause)
	ON_WM_HSCROLL()

	ON_COMMAND(ID_32772, &CMusicPlayerDlg::OnOpenMusicFile)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, &CMusicPlayerDlg::OnNMClickList3)
	ON_NOTIFY(NM_RCLICK, IDC_LIST3, &CMusicPlayerDlg::OnNMRClickList3)
	ON_COMMAND(ID_SFDS_DSDFSD, &CMusicPlayerDlg::OnPlayMic)
	ON_COMMAND(ID_SFDS_ASDSA, &CMusicPlayerDlg::OnDel)
	ON_COMMAND(ID_32777, &CMusicPlayerDlg::OnPlayMic)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON5, &CMusicPlayerDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMusicPlayerDlg::OnBnClickedButton6)
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST3, &CMusicPlayerDlg::OnNMCustomdrawList3)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, &CMusicPlayerDlg::OnNMDblclkList3)
	ON_LBN_SELCHANGE(IDC_LIST4, &CMusicPlayerDlg::OnLbnSelchangeList4)
	ON_BN_CLICKED(IDC_BUTTON7, &CMusicPlayerDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMusicPlayerDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON1, &CMusicPlayerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON18, &CMusicPlayerDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON16, &CMusicPlayerDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON13, &CMusicPlayerDlg::OnBnClickedButton13)
END_MESSAGE_MAP()


// CMusicPlayerDlg ��Ϣ�������

BOOL CMusicPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_DlgBkColor = RGB(100,100,100);
	m_LstCtrlBkColor =  RGB(110,110,110);
	m_LstBoxlBkColor =  RGB(120,120,120);

	
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|WS_EX_LAYERED);
	SetLayeredWindowAttributes(0,200,LWA_ALPHA);
	SetBackgroundColor(m_DlgBkColor);

	

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
			//�󶨿ؼ�IDC_BUTTON1����CMyButton����Ӧ���غ���DrawItem()
			bt->Attach(ID,this);
			//����Button Down�ı���ɫ
			bt->SetDownColor(m_DlgBkColor);
			//����Button Up�ı���ɫ
			bt->SetUpColor(m_DlgBkColor);
		}

		pWnd=pWnd-> GetNextWindow(); 
	}
	//m_ListBox.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)LVS_EX_FULLROWSELECT);  

	//m_ListBox.SetItemHeight(0,30);
	m_ListBox.AddString("��ҳ");
	m_ListBox.AddString("�ղؼ�");
	m_ListBox.AddString("���ص���");
	m_ListBox.AddString("�ҵ�Ǯ��");
	
	
	m_ImgList.Create(24, 24, ILC_COLOR | ILC_MASK, 1, 1);

	 m_listFile.SetImageList(&m_ImgList, LVSIL_NORMAL);//��ʾ����ͼ��

	CString imgPath[] = {"res\\�����\\��ҳ.png","res\\�����\\�ղ�.png","res\\�����\\���ص���.png",
	"res\\�����\\Ǯ��.png"};

	for (int i = 0; i < 4 ; i++)
	{
		CImage img;
		
		img.Load(imgPath[0]);
		HBITMAP hbitmap = img.Detach();
		CBitmap bmp;
		bmp.Attach(hbitmap);
		
		m_uImgID[i] = m_ImgList.Add(&bmp, RGB(255, 255, 255)); //���λͼ��ͼ���б����ظ�ͼ������
	}
	

	
    // m_ListBox.SetItemBackgndColor(RGB(100,100,100),0,2);	
	//m_ListBox.SetItemTextColor(RGB(255,0,0),0,2);


	m_slider.SetRange(0,100);
	m_slider.SetPos(50);
	SetMicrPhoneVolume(50);
	m_vol.SetWindowText("50");
	
	//m_listFile.SetRowHeigt(50);
	SetWindowLong( m_listFile.m_hWnd, GWL_STYLE,  WS_CHILD|WS_VISIBLE|WS_HSCROLL);

	DWORD dwStyle= GetWindowLong(m_listFile.m_hWnd, GWL_STYLE); 
	SetWindowLong( m_listFile.m_hWnd, GWL_STYLE, dwStyle  |LVS_ICON | LVS_SINGLESEL |LVS_NOCOLUMNHEADER|LVS_ALIGNTOP);
	
	m_listFile.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	//m_listFile.SetBkColor(m_LstCtrlBkColor);
	m_listFile.SetIconSpacing(CSize(140, 130));     //����ͼƬ��� 
	
	CString str[] = {"res\\1.jpg","res\\2.jpg","res\\3.jpg"};
	UINT pPic[] = {IDC_STATIC2,IDC_STATIC3,IDC_STATIC4};
	for(int i =0;i<3;i++)
	{
		m_pPic [i] = (CStatic*)GetDlgItem(pPic[i]);						
		CImage* image = new CImage();  
		image->Load(str[i]);  
		m_hBmp[i] = image->Detach(); 

	}

	ShowPic();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMusicPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMusicPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMusicPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMusicPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	if(pScrollBar != NULL )
	{
		// ǿ��ת����CSliderCtrl
		CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
		// ����CSliderCtrl ID ���ж�����һ��CSliderCtrl
		if(pSlider->GetDlgCtrlID() == IDC_SLIDER1)
		{
			long v = m_slider.GetPos();
			SetMicrPhoneVolume(v);
			CString ff;
			ff.Format(_T("%d"),v);
			m_vol.SetWindowText(ff);
		}
	}
}

BOOL CMusicPlayerDlg::ChangeStatus(DWORD NewStatus, DWORD SelectedItem, HDEVINFO hDevInfo)   
{    
	LPTSTR lpszMsg = NULL;    
	HCURSOR hCursor = NULL;    
	try    
	{    
		SP_PROPCHANGE_PARAMS PropChangeParams = {sizeof(SP_CLASSINSTALL_HEADER)};    
		SP_DEVINFO_DATA DeviceInfoData = {sizeof(SP_DEVINFO_DATA)};    
		   
		// Get a handle to the Selected Item.     
		if (!SetupDiEnumDeviceInfo(hDevInfo, SelectedItem, &DeviceInfoData))    
		{    
			//FormatMSG(GetLastError(), &lpszMsg);    
			throw lpszMsg;    
		}    
		// Set the PropChangeParams structure.     
		PropChangeParams.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;    
		PropChangeParams.Scope = DICS_FLAG_GLOBAL;    
		PropChangeParams.StateChange = NewStatus;    
		if (!SetupDiSetClassInstallParams(hDevInfo, &DeviceInfoData, (SP_CLASSINSTALL_HEADER *)&PropChangeParams,    
			sizeof(PropChangeParams)))    
		{    
			//FormatMSG(GetLastError(), &lpszMsg);    
			throw lpszMsg;    
		}    

		// Call the ClassInstaller and perform the change.     
		if (!SetupDiCallClassInstaller(DIF_PROPERTYCHANGE,hDevInfo,&DeviceInfoData))    
		{    
			//FormatMSG(GetLastError(), &lpszMsg);    
			throw lpszMsg;    
		}    
		SetCursor(hCursor);     
		return TRUE;    
	}    
	catch(...)    
	{    
		//SetCursor(hCursor);    
		//::MessageBox(NULL,pszError,_T("��ʾ"),MB_OK);    
		if (NULL != lpszMsg)    
		{    
			LocalFree((HLOCAL)lpszMsg);    
		}     
		return FALSE;    
	}    
}    

BOOL CMusicPlayerDlg::ControlDisk(int nStatus)    
{    
	HRESULT hr;  
	IMMDeviceEnumerator* pDeviceEnumerator=0;  
	IMMDevice* pDevice=0;   
	IMMDeviceCollection *pCollection = NULL;

	try{  
		CoInitialize(0);

		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),NULL,CLSCTX_ALL,__uuidof(IMMDeviceEnumerator),(void**)&pDeviceEnumerator);  
		if(FAILED(hr)) throw "CoCreateInstance";
	
		//return true;  

		hr = pDeviceEnumerator->EnumAudioEndpoints(eCapture, DEVICE_STATE_DISABLED|DEVICE_STATE_ACTIVE,&pCollection);  
		UINT  count;  
		hr = pCollection->GetCount(&count);  

		for(UINT i =0;i<count;i++)
		{
			pCollection->Item(i,&pDevice);

			LPWSTR p = new WCHAR[256];
			pDevice->GetId(&p);

			GUID guid;    
			ZeroMemory(&guid, sizeof(GUID)); 
			CString str(p);
			str = str.Right(str.GetLength()- str.ReverseFind('{')-1);
			str = str.Left(str.ReverseFind('}'));

			UuidFromString((unsigned char *)str.GetBuffer(0), &guid);     
			  
			 guid = GUID_DEVCLASS_MEDIA;
			HDEVINFO hDevInfo = SetupDiGetClassDevs(&guid,NULL,NULL,DIGCF_PRESENT);    
			
			
			  
			SP_DEVINFO_DATA DeviceInfoData;    
			ZeroMemory(&DeviceInfoData, sizeof(SP_DEVINFO_DATA));    
			DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);    
			
				if (1 == nStatus)    
				{    
				    ChangeStatus(DICS_ENABLE, i, hDevInfo);    
				}    
				else if (0 == nStatus)    
				{   
				     ChangeStatus(DICS_DISABLE, i, hDevInfo);    
				}     
			   
			// �ͷ� device information set     
			SetupDiDestroyDeviceInfoList(hDevInfo);    



		}

	}  
	catch(...){  
		
		if(pDevice) pDevice->Release();  
		if(pDeviceEnumerator) pDeviceEnumerator->Release();  
		CoUninitialize(); 
	}  
	return false;  

}    

BOOL CMusicPlayerDlg::SetMicrPhoneVolume(DWORD level)  
{  
	HRESULT hr;  
	IMMDeviceEnumerator* pDeviceEnumerator=0;  
	IMMDevice* pDevice=0;  
	IAudioEndpointVolume* pAudioEndpointVolume=0;  
	IAudioClient* pAudioClient=0;  
	IMMDeviceCollection *pCollection = NULL;

	IPropertyStore *pProps = NULL;  
	LPWSTR pwszID = NULL;  

	level = level>100?100:level;
	level = level<0?0:level;

	try{  
		CoInitialize(0);

		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),NULL,CLSCTX_ALL,__uuidof(IMMDeviceEnumerator),(void**)&pDeviceEnumerator);  
		if(FAILED(hr)) throw "CoCreateInstance"; 

		hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender,eMultimedia,&pDevice);  
		if(FAILED(hr)) throw "GetDefaultAudioEndpoint";  

		hr = pDevice->Activate(__uuidof(IAudioEndpointVolume),CLSCTX_ALL,NULL,(void**)&pAudioEndpointVolume);  
		if(FAILED(hr)) throw "pDevice->Active";  
 
		hr = pDevice->Activate(__uuidof(IAudioClient),CLSCTX_ALL,NULL,(void**)&pAudioClient);  
		if(FAILED(hr)) throw "pDevice->Active";
	 
		if(level<0 || level>100)
		{  
			hr = E_INVALIDARG;  
			throw "Invalid Arg";  
		}  

		float fVolume;  
		fVolume = level/100.0f;  
		hr = pAudioEndpointVolume->SetMasterVolumeLevelScalar(fVolume,&GUID_NULL);  
		if(FAILED(hr)) throw "SetMasterVolumeLevelScalar";  

		pAudioClient->Release();  
		pAudioEndpointVolume->Release();  
		pDevice->Release();  
		pDeviceEnumerator->Release();  
		//return true;  

		hr = pDeviceEnumerator->EnumAudioEndpoints(eCapture, DEVICE_STATE_DISABLED|DEVICE_STATE_ACTIVE,&pCollection);  
		UINT  count;  
		hr = pCollection->GetCount(&count);  

		for(UINT i =0;i<count;i++)
		{
			pCollection->Item(i,&pDevice);

			LPWSTR p = new WCHAR[256];
			pDevice->GetId(&p);


			hr = pDevice->Activate(__uuidof(IAudioEndpointVolume),CLSCTX_ALL,NULL,(void**)&pAudioEndpointVolume); 

			//д״̬
			DWORD dwState=0x00000001;

			HKEY m_hKey;
			DWORD dwType = REG_DWORD;

			if(RegOpenKeyEx((HKEY)HKEY_LOCAL_MACHINE,(LPCTSTR)p, 0, KEY_ALL_ACCESS, &m_hKey) == ERROR_SUCCESS)  
			{  
				if(::RegSetValueEx(m_hKey, (LPCTSTR)"DeviceState", 0, dwType, (LPBYTE)(LPCTSTR)dwState, 4) == ERROR_SUCCESS)  
				{  

				}   
			}  

			pAudioEndpointVolume->SetMasterVolumeLevelScalar(level/100.0f,&GUID_NULL);
		}

	}  
	catch(...){  
		if(pAudioClient) pAudioClient->Release();  
		if(pAudioEndpointVolume) pAudioEndpointVolume->Release();  
		if(pDevice) pDevice->Release();  
		if(pDeviceEnumerator) pDeviceEnumerator->Release();  
		CoUninitialize(); 
	}  
	return false;  
}  

DWORD SpeakerThread(DWORD wPame)
{
	CMusicPlayerDlg* pThis = (CMusicPlayerDlg*)wPame;

	//����������
	pThis->op.dwCallback=NULL; 
	pThis->op.lpstrAlias=NULL; 
	pThis->op.lpstrDeviceType=_T("MPEGAudio");  //�豸���ͣ�������ļ������������� 

	if(pThis->m_fileName == "")
	{
		AfxMessageBox("��ѡ��MP3�ļ�");
		return 0;
	}

	CString str(pThis->m_fileName.c_str());	
	pThis->op.lpstrElementName=str; //_T("D:\\2.mp3"); //�ļ�·�� 
	pThis->op.wDeviceID=NULL;      //���豸�ɹ��Ժ󱣴�����豸�ű��� 
	UINT rs;        //���ܺ������ؽ�� 
	//����������豸���ɹ�����0�����򷵻ش���ţ������������������MCI_OPEN_ELEMENT  
	rs=mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD)&pThis->op);

	mciSendCommand(NULL,MCI_SET,MCI_SET_DOOR_OPEN,NULL);

	DWORD cdlen =pThis->getinfo(pThis->op.wDeviceID,MCI_STATUS_LENGTH);//��ȡ��Ƶ�ļ�����

	if(rs==0)        //�豸�򿪳ɹ��Ͳ����ļ� 
	{ 
		MCI_PLAY_PARMS pp; 
		pp.dwCallback=NULL; 
		pp.dwFrom=0;      //��ʼ���ŵ�λ�� 
		mciSendCommand(pThis->op.wDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)&pp);
		//�����ļ������������������ΪMCI_WAIT����򴰿ڻᱻ������Ϊ�˱����������������ΪMCI_NOTIFY 
	}
	int playtime = cdlen;
	MCI_PLAY_PARMS pp;

	while(1)
	{
		if(stopFlag)
		{
			break;
		}
		if(pauseFlag)
		{
			mciSendCommand (pThis->op.wDeviceID, MCI_PAUSE, 0,(DWORD)(LPVOID) &pp);
			continue;
		}
		else
		{
			mciSendCommand (pThis->op.wDeviceID, MCI_PLAY,MCI_NOTIFY ,(DWORD)(LPVOID) &pp);
		}

		playtime--;
		Sleep(1000);//�����ļ����ȵȴ�����MCI_WAITЧ��һ����cdlen�������Կ��Ʋ���ʱ��
	}
	stopFlag = false;
	pThis->OnStop();        //�ر���Ƶ�ļ� 

	return 0;  
}

void CMusicPlayerDlg::OnPlayMic()
{
	//��˷粥��
	stopFlag = true;
	WaitForSingleObject(hSpeaker,INFINITE);
	//Sleep(1000);
	stopFlag = false;
	pauseFlag = false;

	/*int mixerNum = (int)mixerGetNumDevs();
	for(int i=0;i<mixerNum;i++)
	{
	unsigned long err;
	err = mixerOpen(&m_hMixer,i,0,0,0);
	if(err != MMSYSERR_NOERROR)
	{
	int k = 0;
	}
	}*/

	hSpeaker=CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SpeakerThread,this,NULL,NULL);
	//
}

void CMusicPlayerDlg::OnStop()
{
	//ֹͣ
	stopFlag = true;
	MCI_GENERIC_PARMS gp; 
	gp.dwCallback=NULL; 
	mciSendCommand(op.wDeviceID,MCI_CLOSE,MCI_WAIT,(DWORD)&gp);

}

DWORD CMusicPlayerDlg::getinfo(UINT wDeviceID,DWORD item)
{
	MCI_STATUS_PARMS mcistatusparms;
	mcistatusparms.dwCallback=(DWORD)GetSafeHwnd();
	mcistatusparms.dwItem=item;
	mcistatusparms.dwReturn=0;
	mciSendCommand(wDeviceID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)&mcistatusparms);
	return mcistatusparms.dwReturn;
}

void CMusicPlayerDlg::OnPause()
{
	// ��ͣ

	pauseFlag = !pauseFlag;

}

void CMusicPlayerDlg::OnOpenMusicFile()
{
	CString strFile;
	// �������ļ�
	CFileDialog fileDlg(TRUE ,  // TRUE��Open��FALSE����Save As�ļ��Ի���
		".mp3",  // Ĭ�ϵĴ��ļ�������
		strFile, // Ĭ�ϴ򿪵��ļ��� 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR |OFN_ALLOWMULTISELECT ,  // ��ѡ��
		"MP3�ļ�(*.mp3)|*.mp3||",  // �򿪵��ļ�����
		this);

	TCHAR *pBuffer = new TCHAR[MAX_PATH *200];//�������ͬʱ��20���ļ�
	fileDlg.m_ofn.lpstrFile = pBuffer;
	fileDlg.m_ofn.nMaxFile = MAX_PATH *200;
	fileDlg.m_ofn.lpstrFile[0] = '\0';

	CString strPath= "D:\\";
	fileDlg.m_ofn.lpstrInitialDir=strPath;//��ʼ��·����
	if(fileDlg.DoModal() == IDOK)
	{
		CString cstrfilepath = _T("");
		POSITION pos = fileDlg.GetStartPosition();
		while (pos != NULL)
		{
			strFile = fileDlg.GetNextPathName(pos);//ȡ���ļ�·��
			//strFile = fileDlg.GetPathName();//����ѡ���������ļ�����
			
			string  str = strFile;	
			if(find(m_musicVector.begin(),m_musicVector.end(),str) == m_musicVector.end())
			{
				m_musicVector.push_back(str);
				
			}
		}		
	}
	UpdateList();

}

void CMusicPlayerDlg::OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	 
	int nItem;
	if(pNMLV->uNewState & LVIS_SELECTED|LVIS_FOCUSED)
	{		
		//��������	
		nItem=pNMLV->iItem;
		CString str;
		if(nItem>=0)
		{
			m_fileName = m_musicVector[nItem];
			
		}
		
	}

	*pResult = 0;
}

void CMusicPlayerDlg::OnNMRClickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int nItem=pNMItemActivate->iItem;
	CString str;
	if(nItem>=0)
	{
		m_fileName = m_musicVector[nItem];
		m_fileIndex = nItem;
	}
	

	CMenu menu; //��������Ҫ�õ���cmenu����
	menu.LoadMenu(IDR_MENU2); //װ���Զ�����Ҽ��˵� 
	CMenu *pPopup = menu.GetSubMenu(0); //��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵�

	CPoint point1;//����һ������ȷ�����λ�õ�λ�� 
	GetCursorPos(&point1);//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը����� 

	if (m_listFile.GetSelectedCount() > 0)  //���û��ѡ���б��е���Ŀ
	{	
		pPopup ->TrackPopupMenu(TPM_LEFTALIGN,point1.x,point1.y,this);//��ָ��λ����ʾ�����˵�
	}
	

	*pResult = 0;
}

void CMusicPlayerDlg::OnDel()
{
	m_musicVector.erase(m_musicVector.begin()+m_fileIndex);	
	UpdateList();
}

void CMusicPlayerDlg::UpdateList(void)
{
	m_listFile.DeleteAllItems();
	int row = m_listFile.GetItemCount();
	
	for(auto i = m_musicVector.begin();i != m_musicVector.end();i++)
	{	
		CString indexStr;
		indexStr.Format("%d",row+1);

		CString strFile;
		strFile = i->c_str();
	    strFile=strFile.Mid(strFile.ReverseFind( '\\')+1); 
		
		int index = m_listFile.InsertItem(row,strFile,m_uImgID[0]);
		row++;
		
		
	}
}

void CMusicPlayerDlg::OnBnClickedButton5()
{
	OnOpenMusicFile();
}

void CMusicPlayerDlg::OnBnClickedButton6()
{
	 CDialog::OnOK();
}

void CMusicPlayerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,   HTCAPTION,   MAKELPARAM(point.x,  point.y));   
	//CDialogEx::OnLButtonDown(nFlags, point);
}

HBRUSH CMusicPlayerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor == CTLCOLOR_LISTBOX )
	{
		pDC->SetBkMode(TRANSPARENT);   
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);   
	}

	return hbr;
}

void CMusicPlayerDlg::OnNMCustomdrawList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
 
    *pResult = CDRF_DODEFAULT;
    if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
    {
        *pResult = CDRF_NOTIFYITEMDRAW;
    }
    else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
    {
        *pResult = CDRF_NOTIFYSUBITEMDRAW;
    }   
    else if((CDDS_ITEMPREPAINT|CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage)
    {
		*pResult = 0;  
		NMLVCUSTOMDRAW* pNMCD = (NMLVCUSTOMDRAW*)(pNMHDR);  

		if(CDDS_PREPAINT == pNMCD->nmcd.dwDrawStage)  
		{  
			*pResult = CDRF_NOTIFYITEMDRAW;  
		}  
		else if (CDDS_ITEMPREPAINT == pNMCD->nmcd.dwDrawStage)  
		{  
			*pResult = CDRF_NOTIFYSUBITEMDRAW;  
		}  
		else if((CDDS_ITEMPREPAINT|CDDS_SUBITEM)==pNMCD->nmcd.dwDrawStage)  
		{  
			COLORREF  clrNewTextColor, clrNewBkColor;  
			int nItem = static_cast<int>(pNMCD->nmcd.dwItemSpec);  
			
			clrNewTextColor = RGB(255,255,255);  
			clrNewBkColor = m_LstCtrlBkColor;
			  

			pNMCD->clrText = clrNewTextColor;  
			pNMCD->clrTextBk = clrNewBkColor;  
			*pResult = CDRF_DODEFAULT ;  
		} 
	}
}

void CMusicPlayerDlg::OnNMDblclkList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	OnPlayMic();
	*pResult = 0;
}

void CMusicPlayerDlg::OnLbnSelchangeList4()
{
	//m_ListBox.GetCurSel();
}


void CMusicPlayerDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	ShowWindow(SW_SHOWMINIMIZED);
}


void CMusicPlayerDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	
		CString str;
		GetDlgItem(IDC_BUTTON8)->GetWindowText(str);
		if(str == "ѭ��")
		{
			GetDlgItem(IDC_BUTTON8)->SetWindowText("����");		
		}
		else
		{
			GetDlgItem(IDC_BUTTON8)->SetWindowText("ѭ��");
		}	
	
}

void CMusicPlayerDlg::ShowPic()
{
	// ��ʾͼƬ

	for(int i=0;i<3;i++)
	{
		int index = (i+m_indexPic)%3;
		CRect rc;
		m_pPic[i]->GetClientRect(&rc);
		m_pPic[i]->SetBitmap(m_hBmp[index]);  
		m_pPic[i]->SetWindowPos(NULL,   
			0,   
			0,   
			rc.Width(),   
			rc.Height(),   
			SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER ); 
		
	}
}



void CMusicPlayerDlg::OnBnClickedButton1()
{
	// ����
	m_indexPic--;
	

	m_indexPic = (m_indexPic)%3;

	
	ShowPic();
	if(m_indexPic == 0)
	{
		m_indexPic = 3;
	}
}


void CMusicPlayerDlg::OnBnClickedButton18()
{
	// ����

	m_indexPic++;
	m_indexPic = m_indexPic%3;
	ShowPic();

}


void CMusicPlayerDlg::OnBnClickedButton16()
{
	//����������
	CSuspendDlg dlg;
	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDOK)                 
	{   
		
	}   
	else if (nResponse == IDCANCEL)  
	{   
		
	}
}


void CMusicPlayerDlg::OnBnClickedButton13()
{
	//��¼ע��
	CLoginRegDlg dlg;
	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDOK)                 
	{   

	}   
	else if (nResponse == IDCANCEL)  
	{   

	}
}
