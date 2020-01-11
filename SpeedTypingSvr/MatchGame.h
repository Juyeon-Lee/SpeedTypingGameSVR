#pragma once


// MatchGame 대화 상자

class MatchGame : public CDialogEx
{
	DECLARE_DYNAMIC(MatchGame)

public:
	MatchGame(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MatchGame();
	CSocServer m_socServer; //서버용 소켓
	CSocCom* m_socCom; //통신용 소켓

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MATCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg LPARAM OnAccept(UINT wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTyping;
	CString m_strID;
	CString m_strScore;

	BOOL m_bConnect;	// 다른 쪽과 접속했을 때 TRUE
	int m_wordNum = 15;
	int m_myScore = 0;

	LPARAM OnReceive(UINT wParam, LPARAM lParam);
	BOOL IsGameEnd();
	void EraseCheck(int wordIndex);
	void SetGameEnd();
	CString m_strConnect;
};
