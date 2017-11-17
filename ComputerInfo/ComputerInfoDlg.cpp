
// ComputerInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ComputerInfo.h"
#include "ComputerInfoDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "iphlpapi.h"
#pragma comment(lib, "iphlpapi.lib")


// 个人认为比较简单的方法，如下：
// 增加头文件：#include "iphlpapi.h"
// 包含库文件：#pragma comment(lib, "iphlpapi.lib")
// iphlpapi.lib网上可以下载到。。。
BOOL GetMacAddress(CString &strMac)
{
	PIP_ADAPTER_INFO pAdapterInfo;
	DWORD AdapterInfoSize;
	TCHAR szMac[32] = { 0 };
	DWORD Err;

	AdapterInfoSize = 0;
	Err = GetAdaptersInfo(NULL, &AdapterInfoSize);

	if ((Err != 0) && (Err != ERROR_BUFFER_OVERFLOW))
	{
		TRACE("获得网卡信息失败！");
		return   FALSE;
	}

	//   分配网卡信息内存  
	pAdapterInfo = (PIP_ADAPTER_INFO)GlobalAlloc(GPTR, AdapterInfoSize);
	if (pAdapterInfo == NULL)
	{
		TRACE("分配网卡信息内存失败");
		return   FALSE;
	}

	if (GetAdaptersInfo(pAdapterInfo, &AdapterInfoSize) != 0)
	{
		TRACE(_T("获得网卡信息失败！\n"));
		GlobalFree(pAdapterInfo);
		return   FALSE;
	}

	strMac.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"),
		pAdapterInfo->Address[0],
		pAdapterInfo->Address[1],
		pAdapterInfo->Address[2],
		pAdapterInfo->Address[3],
		pAdapterInfo->Address[4],
		pAdapterInfo->Address[5]);

	GlobalFree(pAdapterInfo);
	return   TRUE;

}


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CComputerInfoDlg 对话框



CComputerInfoDlg::CComputerInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COMPUTERINFO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComputerInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edt_ComputerName);
	DDX_Control(pDX, IDC_EDIT2, edt_Mac);
}

BEGIN_MESSAGE_MAP(CComputerInfoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CComputerInfoDlg 消息处理程序

BOOL CComputerInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	const int MAX_LENGTH = MAX_COMPUTERNAME_LENGTH;
	DWORD dwLength;
	TCHAR buff[MAX_LENGTH];
	::GetComputerName(buff, &dwLength);

	CString computer_name = buff;
	edt_ComputerName.SetWindowText(computer_name);

	CString mac;
	GetMacAddress(mac);
	edt_Mac.SetWindowText(mac);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CComputerInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CComputerInfoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CComputerInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

