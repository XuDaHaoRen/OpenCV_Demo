
// 180814120.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy180814120App: 
// �йش����ʵ�֣������ 180814120.cpp
//

class CMy180814120App : public CWinApp
{
public:
	CMy180814120App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy180814120App theApp;