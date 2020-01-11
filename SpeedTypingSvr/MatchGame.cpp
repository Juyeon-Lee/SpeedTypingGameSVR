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
	, m_word1(_T("함함하다"))
	, m_word10(_T("슬렉스"))
	, m_word11(_T("트리트먼트"))
	, m_word12(_T("치킨"))
	, m_word13(_T("의자"))
	, m_word14(_T("요거트"))
	, m_word15(_T("수맥"))
	, m_word2(_T("괴랄하다"))
	, m_word3(_T("신선함"))
	, m_word4(_T("고구마라떼"))
	, m_word5(_T("카푸치노"))
	, m_word6(_T("드라이기"))
	, m_word7(_T("가방"))
	, m_word8(_T("칠성"))
	, m_word9(_T("장수돌침대"))
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
	DDX_Text(pDX, IDC_STATIC1, m_word1);
	DDX_Text(pDX, IDC_STATIC10, m_word10);
	DDX_Text(pDX, IDC_STATIC11, m_word11);
	DDX_Text(pDX, IDC_STATIC12, m_word12);
	DDX_Text(pDX, IDC_STATIC13, m_word13);
	DDX_Text(pDX, IDC_STATIC14, m_word14);
	DDX_Text(pDX, IDC_STATIC15, m_word15);
	DDX_Text(pDX, IDC_STATIC2, m_word2);
	DDX_Text(pDX, IDC_STATIC3, m_word3);
	DDX_Text(pDX, IDC_STATIC4, m_word4);
	DDX_Text(pDX, IDC_STATIC5, m_word5);
	DDX_Text(pDX, IDC_STATIC6, m_word6);
	DDX_Text(pDX, IDC_STATIC7, m_word7);
	DDX_Text(pDX, IDC_STATIC8, m_word8);
	DDX_Text(pDX, IDC_STATIC9, m_word9);
}


BEGIN_MESSAGE_MAP(MatchGame, CDialogEx)
	ON_MESSAGE(UM_ACCEPT, &MatchGame::OnAccept)
	ON_MESSAGE(UM_RECEIVE, &MatchGame::OnReceive)
END_MESSAGE_MAP()

BOOL MatchGame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	endGameIndex = 0;
	score = _T("");
	m_strScore.Format("%d%s", m_myScore, "점");
	m_bConnect = FALSE;

	GetDlgItem(IDC_EDIT_TYPING)->EnableWindow(FALSE);

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

afx_msg LRESULT MatchGame::OnAccept(WPARAM wParam, LPARAM lParam)
{
	// 클라이언트에서 접속 요청이 왔을 때

	//통신용 소켓을 생성한 뒤
	m_socCom = new CSocCom;
	//서버소켓과 통신소켓을 연결한다.
	m_socCom = m_socServer.GetAcceptSocCom();
	m_socCom->Init(this->m_hWnd);

	m_socCom->Send("접속성공", 256);
	//	m_bConnect = TRUE;

	m_strConnect = "접속중";
	m_bConnect = TRUE;
	GetDlgItem(IDC_EDIT_TYPING)->EnableWindow(TRUE);

	UpdateData(FALSE);
	return TRUE;
}


afx_msg LRESULT MatchGame::OnReceive(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 구현 코드 추가.
	char pTmp[256];
	CString str;
	memset(pTmp, '\0', 256);

	// 데이터를 pTmp에 받는다
	m_socCom->Receive(pTmp, 256);

	//일단은 헤더 없음

	str.Format("%s", pTmp);

	if (str == _T("접속성공"))
	{
		m_bConnect = TRUE;
	}
	else
	{
		EraseCheck(atoi(str),FALSE);
		if (IsGameEnd()) {
			Sleep(1000);
			SetGameEnd();
		}
	}

	return LPARAM();
}


BOOL MatchGame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString str;
	int index;

	// 엔터키 처리
	if ((pMsg->message == WM_KEYDOWN)
		&& pMsg->hwnd == GetDlgItem(IDC_EDIT_TYPING)->m_hWnd
		&& (pMsg->wParam == VK_RETURN)
		&& m_bConnect == TRUE)
	{
		// EDIT TEXT에서 문자열 획득 후, STATIC TEXT들과 비교하는 함수로 전달

		GetDlgItemText(IDC_EDIT_TYPING, str);

		index = staticStringToIndex(str);

		if (index) // 찾은 인덱스로 EraseCheck(인덱스)하면 단어가 삭제
		{
			EraseCheck(index, TRUE);
			UpdateData(FALSE);
			str.Format("%d", index);
			SendGame(str);
		}

		if (IsGameEnd())
		{
			/*str.Format("%s%d%s", "게임이 종료되었습니다!\n최종 스코어 :", m_myScore, "점");
			MessageBox(str);*/
			Sleep(1000);
			SetGameEnd();
		}

		SetDlgItemText(IDC_EDIT_TYPING, "");
		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}



BOOL MatchGame::IsGameEnd()
{
	if (endGameIndex >= 15)
		return TRUE;
	else
		return FALSE;
}

int MatchGame::staticStringToIndex(CString str)
{
	if (str == m_word1)
		return 1;
	else if (str == m_word2)
		return 2;
	else if (str == m_word3)
		return 3;
	else if (str == m_word4)
		return 4;
	else if (str == m_word5)
		return 5;
	else if (str == m_word6)
		return 6;
	else if (str == m_word7)
		return 7;
	else if (str == m_word8)
		return 8;
	else if (str == m_word9)
		return 9;
	else if (str == m_word10)
		return 10;
	else if (str == m_word11)
		return 11;
	else if (str == m_word12)
		return 12;
	else if (str == m_word13)
		return 13;
	else if (str == m_word14)
		return 14;
	else if (str == m_word15)
		return 15;
	else // 맞는 단어 없음
		return 0;
}

void MatchGame::EraseCheck(int wordIndex, BOOL itsMe)
{
	switch (wordIndex)
	{
	case 1:
		(GetDlgItem(IDC_STATIC1))->ShowWindow(FALSE);
		break;
	case 2:
		(GetDlgItem(IDC_STATIC2))->ShowWindow(FALSE);
		break;
	case 3:
		(GetDlgItem(IDC_STATIC3))->ShowWindow(FALSE);
		break;
	case 4:
		(GetDlgItem(IDC_STATIC4))->ShowWindow(FALSE);
		break;
	case 5:
		(GetDlgItem(IDC_STATIC5))->ShowWindow(FALSE);
		break;
	case 6:
		(GetDlgItem(IDC_STATIC6))->ShowWindow(FALSE);
		break;
	case 7:
		(GetDlgItem(IDC_STATIC7))->ShowWindow(FALSE);
		break;
	case 8:
		(GetDlgItem(IDC_STATIC8))->ShowWindow(FALSE);
		break;
	case 9:
		(GetDlgItem(IDC_STATIC9))->ShowWindow(FALSE);
		break;
	case 10:
		(GetDlgItem(IDC_STATIC10))->ShowWindow(FALSE);
		break;
	case 11:
		(GetDlgItem(IDC_STATIC11))->ShowWindow(FALSE);
		break;
	case 12:
		(GetDlgItem(IDC_STATIC12))->ShowWindow(FALSE);
		break;
	case 13:
		(GetDlgItem(IDC_STATIC13))->ShowWindow(FALSE);
		break;
	case 14:
		(GetDlgItem(IDC_STATIC14))->ShowWindow(FALSE);
		break;
	case 15:
		(GetDlgItem(IDC_STATIC15))->ShowWindow(FALSE);
		break;
	default:
		return;
	}

	// 일치하는 단어 찾았을 때만
	endGameIndex++;
	if (itsMe)//내가 맞췄을 때만 내 점수 오른다.
	{
		m_myScore++; 
		m_strScore.Format("%d%s", m_myScore, "점");
	}
	
	score.Format("%d", endGameIndex);
}


void MatchGame::SetGameEnd()
{
	int competitorScore = 15 - m_myScore;
	if (competitorScore > m_myScore)
		MessageBox("패");
	else
		MessageBox("승");
}

void MatchGame::SendGame(CString strTmp)
{
	// 데이터 전송
	UpdateData(TRUE);
	char pTmp[256];

	memset(pTmp, '\0', 256);
	sprintf_s(pTmp, 256, "%s", strTmp);

	m_socCom->Send(pTmp, 256);
}

