#pragma once

// CSocServer 명령 대상

class CSocServer : public CSocket
{
public:
	CSocServer();
	virtual ~CSocServer();

	HWND m_hWnd; //메인 윈도우 핸들
	CSocCom m_socCom; //접속 요청이 왔을 때 연결할 소켓

	void Init(HWND hWnd);
	virtual void OnAccept(int nErrorCode);
	CSocCom* GetAcceptSocCom();
};


