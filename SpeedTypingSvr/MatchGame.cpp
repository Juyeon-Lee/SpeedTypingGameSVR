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
	, m_strScore(_T("0점"))
	, m_strConnect(_T("연결 안 됨"))
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
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strConnect);
}


BEGIN_MESSAGE_MAP(MatchGame, CDialogEx)
	ON_MESSAGE(UM_ACCEPT, (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnAccept)
END_MESSAGE_MAP()

BOOL MatchGame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_socCom = NULL;
	//서버 소켓을 생성(포트번호 5000)
	m_socServer.Create(5000);
	//클라이언트의 접속을 기다린다.
	m_socServer.Listen();
	//소켓 클래스와 메인 윈도우(여기에서는 CChatServerDlg)를 연결한다.
	m_socServer.Init(this->m_hWnd);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


// MatchGame 메시지 처리기

//LPARAM MatchGame::OnAccept(UINT wParam, LPARAM IParam)
//{
//	// 클라이언트에서 접속 요청이 왔을 때
//
//	//통신용 소켓을 생성한 뒤
//	m_socCom = new CSocCom;
//	//서버소켓과 통신소켓을 연결한다.
//	m_socCom = m_socServer.GetAcceptSocCom();
//	m_socCom->Init(this->m_hWnd);
//
//	m_socCom->Send("접속성공", 256);
//	m_strConnect = "연결됨";
//	m_bConnect = TRUE;
//
//	UpdateData(FALSE);
//	return TRUE;
//}

LPARAM MatchGame::OnReceive(UINT wParam, LPARAM lParam)
{
	// TODO: 여기에 구현 코드 추가.
	char pTmp[256];
	CString strTmp, str;
	memset(pTmp, '\0', 256);

	// 데이터를 pTmp에 받는다
	m_socCom->Receive(pTmp, 256);

	//일단은 헤더 없음

	str.Format("%s", pTmp);

	EraseCheck(atoi(str));

	if (IsGameEnd()) {
		Sleep(1000);
		SetGameEnd();
	}


	return LPARAM();
}

BOOL MatchGame::IsGameEnd()
{
	if (m_wordNum)
		return TRUE;
	else
		return FALSE;
}


void MatchGame::EraseCheck(int wordIndex)
{
	
	switch (wordIndex)
	{
	case 1:
		(GetDlgItem(IDC_STATIC1))->ShowWindow(FALSE);
	case 2:
		(GetDlgItem(IDC_STATIC2))->ShowWindow(FALSE);
	case 3:
		(GetDlgItem(IDC_STATIC3))->ShowWindow(FALSE);
	case 4:
		(GetDlgItem(IDC_STATIC4))->ShowWindow(FALSE);
	case 5:
		(GetDlgItem(IDC_STATIC5))->ShowWindow(FALSE);
	case 6:
		(GetDlgItem(IDC_STATIC6))->ShowWindow(FALSE);
	case 7:
		(GetDlgItem(IDC_STATIC7))->ShowWindow(FALSE);
	case 8:
		(GetDlgItem(IDC_STATIC8))->ShowWindow(FALSE);
	case 9:
		(GetDlgItem(IDC_STATIC9))->ShowWindow(FALSE);
	case 10:
		(GetDlgItem(IDC_STATIC10))->ShowWindow(FALSE);
	case 11:
		(GetDlgItem(IDC_STATIC11))->ShowWindow(FALSE);
	case 12:
		(GetDlgItem(IDC_STATIC12))->ShowWindow(FALSE);
	case 13:
		(GetDlgItem(IDC_STATIC13))->ShowWindow(FALSE);
	case 14:
		(GetDlgItem(IDC_STATIC14))->ShowWindow(FALSE);
	case 15:
		(GetDlgItem(IDC_STATIC15))->ShowWindow(FALSE);
	default:
		break;
	}
}


void MatchGame::SetGameEnd()
{
	int competitorScore = 15 - m_myScore;
	if (competitorScore > m_myScore)
		MessageBox("패");
	else
		MessageBox("승");
}




LPARAM MatchGame::OnAccept(UINT wParam, LPARAM lParam)
{
	// TODO: 여기에 구현 코드 추가.
	// 클라이언트에서 접속 요청이 왔을 때

	//통신용 소켓을 생성한 뒤
	m_socCom = new CSocCom;
	//서버소켓과 통신소켓을 연결한다.
	m_socCom = m_socServer.GetAcceptSocCom();
	m_socCom->Init(this->m_hWnd);

	m_socCom->Send("접속성공", 256);

	m_strConnect = "클라이언트 접속중";

	UpdateData(FALSE);
	return TRUE;
}