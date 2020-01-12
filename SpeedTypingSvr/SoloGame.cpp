// SoloGame.cpp: 구현 파일
//

#include "pch.h"
#include "SpeedTypingSvr.h"
#include "SoloGame.h"
#include "afxdialogex.h"


// SoloGame 대화 상자

IMPLEMENT_DYNAMIC(SoloGame, CDialogEx)

SoloGame::SoloGame(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SOLO1, pParent)
	, m_strTyping()

{
	SetWord();
	endcnt = 1;
	cnt = 1;
}

SoloGame::~SoloGame()
{
}

void SoloGame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_TYPING, m_strTyping);

	DDX_Control(pDX, IDC_STATIC1_SOLO, m_txt1);
	DDX_Control(pDX, IDC_STATIC10_SOLO, m_txt10);
	DDX_Control(pDX, IDC_EDIT_TYPING, m_strTyping);
	DDX_Control(pDX, IDC_STATIC11_SOLO, m_txt11);
	DDX_Control(pDX, IDC_STATIC12_SOLO, m_txt12);
	DDX_Control(pDX, IDC_STATIC13_SOLO, m_txt13);
	DDX_Control(pDX, IDC_STATIC14_SOLO, m_txt14);
	DDX_Control(pDX, IDC_STATIC15_SOLO, m_txt15);
	DDX_Control(pDX, IDC_STATIC2_SOLO, m_txt2);
	DDX_Control(pDX, IDC_STATIC3_SOLO, m_txt3);
	DDX_Control(pDX, IDC_STATIC4_SOLO, m_txt4);
	DDX_Control(pDX, IDC_STATIC5_SOLO, m_txt5);
	DDX_Control(pDX, IDC_STATIC6_SOLO, m_txt6);
	DDX_Control(pDX, IDC_STATIC7_SOLO, m_txt7);
	DDX_Control(pDX, IDC_STATIC8_SOLO, m_txt8);
	DDX_Control(pDX, IDC_STATIC9_SOLO, m_txt9);
}


BEGIN_MESSAGE_MAP(SoloGame, CDialogEx)
END_MESSAGE_MAP()


// SoloGame 메시지 처리기
void SoloGame::SetWord()//db에 연결 시 필요 없음 // 테스트를 위한 함수
{
	POSITION pos = m_string_list.GetHeadPosition();//문자열의 시작위치를 
	if (pos != NULL)//만약 문자열에 단어가 있다면
		m_string_list.RemoveAll();//모든 단어를 지운다.

		//리스트에 문자 추가

	m_string_list.AddTail(_T("발바닥"));
	m_string_list.AddTail(_T("아깝다"));
	m_string_list.AddTail(_T("싫어하다"));
	m_string_list.AddTail(_T("핏줄기"));
	m_string_list.AddTail(_T("힘겹다"));
	m_string_list.AddTail(_T("저녁때"));
	m_string_list.AddTail(_T("비슷비슷"));
	m_string_list.AddTail(_T("능동태"));
	m_string_list.AddTail(_T("남자"));
	m_string_list.AddTail(_T("내리다"));
	m_string_list.AddTail(_T("싱숭생숭"));
	m_string_list.AddTail(_T("설레다"));
	m_string_list.AddTail(_T("미꾸라지"));
	m_string_list.AddTail(_T("토지"));
	m_string_list.AddTail(_T("메뚜기"));
}

BOOL SoloGame::PreTranslateMessage(MSG* pMsg)//edit control 에서 enter 로 값 비교
{

	CString strText = _T("");
	m_strTyping.GetWindowTextA(strText);


	POSITION pos = m_string_list.GetHeadPosition();
	//POSITION remove_pos;
	cnt = 1;


	ViewWord();
	if (pMsg->message == WM_KEYDOWN && pMsg->hwnd == GetDlgItem(IDC_EDIT_TYPING)->m_hWnd)
	{
		if (pMsg->wParam == VK_RETURN)
		{

			while (pos != NULL && IsGameEnd(endcnt)) {

				if (strText == m_string_list.GetAt(pos)) {
					m_strTyping.SetWindowTextA("");
					EraseCheck(cnt);
					endcnt++;

					//랜덤한 값을 만약 받는다면
					/*remove_pos = pos;
					m_string_list.GetNext(pos);
					m_string_list.RemoveAt(pos);*/
					break;
				}
				else {
					m_string_list.GetNext(pos);
					cnt++;
				}

			}
			if (!IsGameEnd(endcnt))
				EraseCheck(cnt);

			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void SoloGame::ViewWord()
{
	SetDlgItemText(IDC_STATIC1_SOLO, _T("발바닥"));
	SetDlgItemText(IDC_STATIC2_SOLO, _T("아깝다"));
	SetDlgItemText(IDC_STATIC3_SOLO, _T("싫어하다"));
	SetDlgItemText(IDC_STATIC4_SOLO, _T("핏줄기"));
	SetDlgItemText(IDC_STATIC5_SOLO, _T("힙겹다"));
	SetDlgItemText(IDC_STATIC6_SOLO, _T("저녁때"));
	SetDlgItemText(IDC_STATIC7_SOLO, _T("비슷비슷"));
	SetDlgItemText(IDC_STATIC8_SOLO, _T("능동태"));
	SetDlgItemText(IDC_STATIC9_SOLO, _T("남자"));
	SetDlgItemText(IDC_STATIC10_SOLO, _T("내리다"));
	SetDlgItemText(IDC_STATIC11_SOLO, _T("싱숭생숭"));
	SetDlgItemText(IDC_STATIC12_SOLO, _T("설레다"));
	SetDlgItemText(IDC_STATIC13_SOLO, _T("미꾸라지"));
	SetDlgItemText(IDC_STATIC14_SOLO, _T("토지"));
	SetDlgItemText(IDC_STATIC15_SOLO, _T("메뚜기"));


}
void SoloGame::EraseCheck(int wordIndex)
{
	// (GetDlgItem(IDC_BT_EMCSTOP))->ShowWindow(FALSE);

	switch (wordIndex)
	{
	case 1:
		(GetDlgItem(IDC_STATIC1_SOLO))->ShowWindow(FALSE);
		break;
	case 2:
		(GetDlgItem(IDC_STATIC2_SOLO))->ShowWindow(FALSE);
		break;
	case 3:
		(GetDlgItem(IDC_STATIC3_SOLO))->ShowWindow(FALSE);
		break;
	case 4:
		(GetDlgItem(IDC_STATIC4_SOLO))->ShowWindow(FALSE);
		break;
	case 5:
		(GetDlgItem(IDC_STATIC5_SOLO))->ShowWindow(FALSE);
		break;
	case 6:
		(GetDlgItem(IDC_STATIC6_SOLO))->ShowWindow(FALSE);
		break;
	case 7:
		(GetDlgItem(IDC_STATIC7_SOLO))->ShowWindow(FALSE);
		break;
	case 8:
		(GetDlgItem(IDC_STATIC8_SOLO))->ShowWindow(FALSE);
		break;
	case 9:
		(GetDlgItem(IDC_STATIC9_SOLO))->ShowWindow(FALSE);
		break;
	case 10:
		(GetDlgItem(IDC_STATIC10_SOLO))->ShowWindow(FALSE);
		break;
	case 11:
		(GetDlgItem(IDC_STATIC11_SOLO))->ShowWindow(FALSE);
		break;
	case 12:
		(GetDlgItem(IDC_STATIC12_SOLO))->ShowWindow(FALSE);
		break;
	case 13:
		(GetDlgItem(IDC_STATIC13_SOLO))->ShowWindow(FALSE);
		break;
	case 14:
		(GetDlgItem(IDC_STATIC14_SOLO))->ShowWindow(FALSE);
		break;
	case 15:
		(GetDlgItem(IDC_STATIC15_SOLO))->ShowWindow(FALSE);
		break;
	default:
		break;
	}
}
BOOL SoloGame::IsGameEnd(int endcnt)
{
	if (endcnt == 1) {
		startTime = clock();
		return TRUE;
	}
	else if (endcnt < 16)
		return TRUE;
	else if (endcnt == 16) {
		endTime = clock();
		result = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
		CString strResult;
		strResult.Format(_T("%.3f"), result);
		EraseCheck(cnt);

		MessageBox(_T("걸린 시간 :" + strResult + "초"), _T("연습결과"), MB_ICONERROR);
		return FALSE;
	}
	else
		return FALSE;
}