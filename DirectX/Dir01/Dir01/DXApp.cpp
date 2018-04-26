#include "DXApp.h"

// �޽��� ���ν��� ������ ��ȸ�ϴµ� ����ϱ� ���� ����.
DXApp* g_pApp = NULL;

LRESULT CALLBACK MainMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	// g_pApp ������ �����Ǹ� MsgProc ���.
	if (g_pApp) return g_pApp->MegProc(hwnd, msg, wParam, lParam);
	// �׷��� ������ ������ �⺻ ���ν��� �Լ� ȣ��
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
	// ���� �޼��� ó��.
	MSG msg;                  // Ȥ�� MSG msg = {0}; �ص� �ȴ�.
	// ���� �ʱ�ȭ.
	ZeroMemory(&msg, sizeof(MSG));
	while (msg.message != WM_QUIT) {
		// �޼��� ó��
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) { // �Ǵٸ� �Լ��� GetMessage(); �� DX �Ҷ��� �Ⱦ�
			// �޼��� �ؼ�.
			TranslateMessage(&msg);
			// �޼��� ����.
			DispatchMessage(&msg); // �޼��� �ؼ��Լ��� �޼��� �����Լ��� �׻� ������ �����Ѵ�.
		}
		else {  // DX ������ ����.
			Update();
			Render();
		}
	}

	return (int)msg.wParam;   // 
}

bool DXApp::Init()
{
	// ������ �ʱ�ȭ
	if (InitWindow() == false) {
		return false;
	}
	return true;
}

bool DXApp::InitWindow()
{
	// ������ Ŭ���� �� ����/����.
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszClassName = "WindowClass";  // �� ���α׷� �ȿ� â�� �������� ��� �� className ������ ������ ��
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = MainMsgProc;

	// ������ Ŭ���� ���.
	if (RegisterClassEx(&wc) == false) {
		return false;
	}

	// ������ ����.
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
		if (wParam == VK_ESCAPE) { // ESC Ű ���ȴ��� Ȯ��
			if (MessageBox(NULL, "��������?", "������", MB_YESNO | MB_ICONQUESTION) == IDYES) {
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