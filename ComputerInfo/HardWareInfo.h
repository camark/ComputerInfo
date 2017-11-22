#pragma once
class CHardWareInfo
{
public:
	CHardWareInfo();
	~CHardWareInfo();

public:
	BOOL GetComputerName(CString& ret);
	BOOL GetMacAddress(CString &strMac);

	BOOL GetMemSize(CString &strMem);
};

