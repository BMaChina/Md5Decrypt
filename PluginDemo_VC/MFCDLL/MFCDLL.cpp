// MFCDLL.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "MFCDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#import "C:\\Windows\\System32\\WinHttpCom.dll" no_namespace
//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CMFCDLLApp

BEGIN_MESSAGE_MAP(CMFCDLLApp, CWinApp)
END_MESSAGE_MAP()


// CMFCDLLApp ����

CMFCDLLApp::CMFCDLLApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMFCDLLApp ����

CMFCDLLApp theApp;


// CMFCDLLApp ��ʼ��

BOOL CMFCDLLApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


CString GetMidStrByLAndR(CString& strSrc, CString strLeft, CString strRight)
{
	CString strRet;
	int eIndxBegin = strSrc.Find(strLeft);
	if (eIndxBegin != -1)
	{
		eIndxBegin += strLeft.GetLength();
		int eIndxEnd = strSrc.Find(strRight, eIndxBegin);
		if (eIndxEnd != -1)
		{
			strRet += strSrc.Mid(eIndxBegin, eIndxEnd-eIndxBegin);
			return strRet;
			
		}
	}
	return strRet;
}


CString GetMd5D(CString strMd5)
{
	CoInitialize(NULL);
	IWinHttpRequestPtr pHttp = NULL;
	HRESULT hr = pHttp.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hr))
	{
		CoUninitialize();
		return FALSE;
	}

	CString strGetMd5;
	strGetMd5.Format(_T("http://md5.syue.com/ShowMD5Info.asp?GetType=ShowInfo&no-cache=0.2149362659992714&md5_str=%s&_="), strMd5);
	pHttp->Open(_T("GET"), strGetMd5.AllocSysString());
	if (FAILED(hr))
	{
		CoUninitialize();
		return FALSE;
	}
	pHttp->SetRequestHeader(_T("Referer"), _T("http://md5.syue.com/"));
	pHttp->Send();
	if (FAILED(hr))
	{
		CoUninitialize();
		return FALSE;
	}

	_variant_t varRspBody = pHttp->GetResponseBody();
	ULONG dataLen = varRspBody.parray->rgsabound[0].cElements;
	char *pContenBuffer = (char *)varRspBody.parray->pvData;
	CString strContenBuffer;
	strContenBuffer = pContenBuffer;
	CString MD5 = GetMidStrByLAndR(strContenBuffer, _T("height:25px\">"), _T("</span"));
	return MD5;
}