#include "DXApp.h"
#include "DXUtill.h"
#include <d3d11.h>
#include <D3DX11.h>

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

	pDevice = NULL;
	pDeviceContext = NULL;  
	pSwapChain = NULL;     
	pRenderTargetView = NULL; 
}

DXApp::~DXApp()
{
	Memory::SafeRelease(pDevice);
	Memory::SafeRelease(pDeviceContext);
	Memory::SafeRelease(pSwapChain);
	Memory::SafeRelease(pRenderTargetView);
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
	// 윈도우 초기화.
	if (InitWindow() == false) {
		return false;
	}

	// DirectX 초기화.
	if (InitDirect3D() == false) {
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

bool DXApp::InitDirect3D()
{
	// 스왑 체인 정보 설정.
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 1;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = hwnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // 화면크기가 변경되면 갱신
	swapDesc.BufferDesc.Width = clientWidth;
	swapDesc.BufferDesc.Height = clientHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;   // 분자
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;  // 분모
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	
	// 장치 및 스왑체인 생성.
	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &swapDesc, &pSwapChain, &pDevice, NULL, &pDeviceContext);

	// 오류 확인
	// if(SUCCEEDED(hr))        // 성공하면 S_OK
	if (FAILED(hr)) {           // 실패하면 E_FAIL
		MessageBox(NULL, "장치 생성 실패", "오류", MB_OK);
		return false;
	}

	// 2D 텍스쳐 생성(렌더 타겟 용).
	ID3D11Texture2D* pBackBufferTexture;
	hr = pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), (void**)&pBackBufferTexture);

	if (FAILED(hr)) {
		MessageBox(NULL, "스왑 버퍼 생성 실패", "오류", MB_OK);
		return false;
	}

	hr = pDevice->CreateRenderTargetView(pBackBufferTexture, NULL, &pRenderTargetView);

	if (FAILED(hr)) {
		MessageBox(NULL, "렌더 타겟 뷰 생성 실패", "오류", MB_OK);
		return false;
	}
	// 렌더 타겟 뷰 바인딩. 파이프 라인에 연결.
	pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);

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