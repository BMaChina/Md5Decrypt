// MFCDLL.h : MFCDLL DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCDLLApp
// �йش���ʵ�ֵ���Ϣ������� MFCDLL.cpp
//

class CMFCDLLApp : public CWinApp
{
public:
	CMFCDLLApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
