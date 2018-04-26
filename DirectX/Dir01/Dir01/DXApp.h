#pragma once
#include <Windows.h>

class DXApp
{
public:

public:
	DXApp(HINSTANCE hinstance);
	virtual ~DXApp();

	// 메인 메세지 루프.
	int Run();

	// 프레임 워크 메소드.
	virtual bool Init();
	virtual void Update() = 0;    // 상속받는 클래스가 반드시 정의해주어야하는 함수를 명시하는 방법
	virtual void Render() = 0;
	virtual LRESULT MegProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);  // 윈도우에서 메세지를 보내면 그 메세지를 받을 수 있는 콜백함수
	
protected:
	// Win32 멤버 변수
	HWND hwnd;
	HINSTANCE hinstance;
	UINT clientWidth;
	UINT clientHeight;
	LPCSTR appTitle;   // 창의 이름을 저장하는 문자열
	DWORD wndStyle;  // 모르면 F12 를 눌러서 정의를 타고 올라가봐라

protected:
	// Win32 메소드.
	// 윈도우 초기화 함수. ( 주석 마지막에 . 을 찍으면 컴파일시 바이트당 전 코드랑 묶이는 경우가 없다.)
	bool InitWindow();
};

