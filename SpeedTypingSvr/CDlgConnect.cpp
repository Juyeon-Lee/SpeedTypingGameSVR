// CDlgConnect.cpp: 구현 파일
//

#include "pch.h"
#include "SpeedTypingSvr.h"
#include "CDlgConnect.h"
#include "afxdialogex.h"


// CDlgConnect 대화 상자

IMPLEMENT_DYNAMIC(CDlgConnect, CDialogEx)

CDlgConnect::CDlgConnect(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CDlgConnect::~CDlgConnect()
{
}

void CDlgConnect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgConnect, CDialogEx)
END_MESSAGE_MAP()


// CDlgConnect 메시지 처리기
