#include "DXApp.h"

// 메시지 프로시져 설정을 우회하는데 사용하기 위해 생성.
DXApp* g_pApp = NULL;

LRESULT CALLBACK MainMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	// g_pApp 변수가 설정되면 MsgProc 사용.
	if (g_pApp) return g_pApp->MegProc(hwnd, msg, wParam, lParam);
	// 그렇지 않응면 윈도우 기본 프로시저 함수 호출
	else return DefWindowProc(hwnd, msg, wParam, lParam);
}

DXApp::DXApp(HINSTANCE hinstance)
{
	hwnd = NULL;
	this->hinstance = hinstance;
	clientWidth =800;
	clientHeight = 600;
	appTitle = "Engine00 - Win32 Setup";  
	wndStyle = WS_OVERLAPPEDWINDOW;  
	g_pApp = this;
}


DXApp::~DXApp()
{
}

int DXApp::Run()
{
	// 메인 메세지 처리.
	MSG msg;                  // 혹은 MSG msg = {0}; 해도 된다.
	// 변수 초기화.
	ZeroMemory(&msg, sizeof(MSG));
	while (msg.message != WM_QUIT) {
		// 메세지 처리
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) { // 또다른 함수인 GetMessage(); 는 DX 할때는 안씀
			// 메세지 해석.
			TranslateMessage(&msg);
			// 메세지 전달.
			DispatchMessage(&msg); // 메세지 해석함수와 메세지 전달함수는 항상 쌍으로 동작한다.
		}
		else {  // DX 렌더링 루프.
			Update();
			Render();
		}
	}

	return (int)msg.wParam;   // 
}

bool DXApp::Init()
{
	// 윈도우 초기화
	if (InitWindow() == false) {
		return false;
	}
	return true;
}

bool DXApp::InitWindow()
{
	// 윈도우 클래스 값 생성/설정.
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszClassName = "WindowClass";  // 이 프로그램 안에 창을 여러가지 띄울 때 className 가지고 구분을 함
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = MainMsgProc;

	// 윈도우 클래스 등록.
	if (RegisterClassEx(&wc) == false) {
		return false;
	}

	// 윈도우 생성.
	this->hwnd = CreateWindow("WindowClass", this->appTitle, this->wndStyle, 0, 0, clientWidth, clientHeight, NULL, NULL, hinstance, NULL);

	if (hwnd == NULL) {
		return false;
	}

	ShowWindow(hwnd, SW_SHOW);

	return true;
}

LRESULT DXApp::MegProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) { // ESC 키 눌렸는지 확인
			if (MessageBox(NULL, "꺼져버려?", "꺼지기", MB_YESNO | MB_ICONQUESTION) == IDYES) {
				DestroyWindow(this->hwnd);
			}
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default: return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return LRESULT();
}