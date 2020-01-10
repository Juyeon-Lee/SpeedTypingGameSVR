// MatchGame.cpp: 구현 파일
//

#include "pch.h"
#include "SpeedTypingSvr.h"
#include "MatchGame.h"
#include "afxdialogex.h"


// MatchGame 대화 상자

IMPLEMENT_DYNAMIC(MatchGame, CDialogEx)

MatchGame::MatchGame(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MATCH, pParent)
	, m_strTyping(_T(""))
	, m_strID(_T(""))
	, m_strScore(_T(""))
{

}

MatchGame::~MatchGame()
{
}

void MatchGame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TYPING, m_strTyping);
	DDX_Text(pDX, IDC_STATIC_ID, m_strID);
	DDX_Text(pDX, IDC_STATIC_SCORE, m_strScore);
}


BEGIN_MESSAGE_MAP(MatchGame, CDialogEx)
END_MESSAGE_MAP()


// MatchGame 메시지 처리기
