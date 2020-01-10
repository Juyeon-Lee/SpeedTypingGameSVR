#pragma once


// MatchGame 대화 상자

class MatchGame : public CDialogEx
{
	DECLARE_DYNAMIC(MatchGame)

public:
	MatchGame(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MatchGame();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MATCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTyping;
	CString m_strID;
	CString m_strScore;
};
