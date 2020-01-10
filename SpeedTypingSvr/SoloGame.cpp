// SoloGame.cpp: 구현 파일
//

#include "pch.h"
#include "SpeedTypingSvr.h"
#include "SoloGame.h"
#include "afxdialogex.h"


// SoloGame 대화 상자

IMPLEMENT_DYNAMIC(SoloGame, CDialogEx)

SoloGame::SoloGame(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SOLO, pParent)
	, m_strTyping(_T(""))
	, m_strID(_T(""))
	, m_strTime(_T(""))
{

}

SoloGame::~SoloGame()
{
}

void SoloGame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TYPING, m_strTyping);
	DDX_Text(pDX, IDC_STATIC_ID, m_strID);
	DDX_Text(pDX, IDC_STATIC_SCORE, m_strTime);
}


BEGIN_MESSAGE_MAP(SoloGame, CDialogEx)
END_MESSAGE_MAP()


// SoloGame 메시지 처리기
