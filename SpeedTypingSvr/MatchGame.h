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

	afx_msg LRESULT OnAccept(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CString m_strTyping;
	CString m_strID;
	CString m_strScore;
	CString m_strConnect;

	CString m_word1;
	CString m_word10;
	CString m_word11;
	CString m_word12;
	CString m_word13;
	CString m_word14;
	CString m_word15;
	CString m_word2;
	CString m_word3;
	CString m_word4;
	CString m_word5;
	CString m_word6;
	CString m_word7;
	CString m_word8;
	CString m_word9;

	BOOL m_bConnect;	// 다른 쪽과 접속했을 때 TRUE
	int m_wordNum = 15;
	int m_myScore = 0;
	int endGameIndex;
	CString score;

	BOOL IsGameEnd();
	int staticStringToIndex(CString str);
	void EraseCheck(int wordIndex, BOOL itsMe);
	void SetGameEnd();
	void SendGame(CString strTmp);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
