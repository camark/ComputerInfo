#include "stdafx.h"
#include "HardWareInfo.h"
#include "iphlpapi.h"
#pragma comment(lib, "iphlpapi.lib")

CHardWareInfo::CHardWareInfo()
{
}


CHardWareInfo::~CHardWareInfo()
{
}

BOOL CHardWareInfo::GetComputerName(CString& ret)
{	
	DWORD dwLength;
	TCHAR buff[MAX_COMPUTERNAME_LENGTH];
	int ilen = ::GetComputerName(buff, &dwLength);

	if (ilen > 0) {
		ret = buff;
		return TRUE;
	}
	else {
		TRACE("获取计算机名失败");
		return FALSE;
	}
}

BOOL CHardWareInfo::GetMacAddress(CString & strMac)
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

BOOL CHardWareInfo::GetMemSize(CString & strMem)
{
	
		MEMORYSTATUSEX        Meminfo;
		double                dSize;

		typedef BOOL(WINAPI * Fun_GlobalMemoryStatusEx)(
			LPMEMORYSTATUSEX lpBuffer);

		Fun_GlobalMemoryStatusEx        GlobalMemoryStatusEx_;
		GlobalMemoryStatusEx_ = (Fun_GlobalMemoryStatusEx)GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "GlobalMemoryStatusEx");
		if (GlobalMemoryStatusEx_)
		{
			memset(&Meminfo, 0, sizeof(Meminfo));
			Meminfo.dwLength = sizeof(Meminfo);

			GlobalMemoryStatusEx_(&Meminfo);

			if (Meminfo.dwLength != sizeof(MEMORYSTATUSEX)) {
				TRACE("获取内存出差");
				return FALSE;
			}


			dSize = (double)Meminfo.ullTotalPhys;
			dSize /= 1024.0;
			dSize /= 1024.0;
			dSize += 0.5;

			strMem.Format(_T("%.0f KB"), dSize);
			return TRUE;
		}
		else
		{
			TRACE("Find GlobalMemoryStatusEx error!");
			return FALSE;
		}
	
}
