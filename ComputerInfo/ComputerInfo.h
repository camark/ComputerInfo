
// ComputerInfo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CComputerInfoApp: 
// �йش����ʵ�֣������ ComputerInfo.cpp
//

class CComputerInfoApp : public CWinApp
{
public:
	CComputerInfoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CComputerInfoApp theApp;