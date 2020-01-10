#pragma once


// SoloGame 대화 상자

class SoloGame : public CDialogEx
{
	DECLARE_DYNAMIC(SoloGame)

public:
	SoloGame(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SoloGame();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SOLO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTyping;
	CString m_strID;
	CString m_strTime;
};
