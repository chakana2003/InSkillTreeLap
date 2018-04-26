#include "DXApp.h"
#include "DXUtill.h"
#include <d3d11.h>
#include <D3DX11.h>

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
	// ������ �ʱ�ȭ.
	if (InitWindow() == false) {
		return false;
	}

	// DirectX �ʱ�ȭ.
	if (InitDirect3D() == false) {
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

bool DXApp::InitDirect3D()
{
	// ���� ü�� ���� ����.
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 1;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = hwnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // ȭ��ũ�Ⱑ ����Ǹ� ����
	swapDesc.BufferDesc.Width = clientWidth;
	swapDesc.BufferDesc.Height = clientHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;   // ����
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;  // �и�
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	
	// ��ġ �� ����ü�� ����.
	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &swapDesc, &pSwapChain, &pDevice, NULL, &pDeviceContext);

	// ���� Ȯ��
	// if(SUCCEEDED(hr))        // �����ϸ� S_OK
	if (FAILED(hr)) {           // �����ϸ� E_FAIL
		MessageBox(NULL, "��ġ ���� ����", "����", MB_OK);
		return false;
	}

	// 2D �ؽ��� ����(���� Ÿ�� ��).
	ID3D11Texture2D* pBackBufferTexture;
	hr = pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), (void**)&pBackBufferTexture);

	if (FAILED(hr)) {
		MessageBox(NULL, "���� ���� ���� ����", "����", MB_OK);
		return false;
	}

	hr = pDevice->CreateRenderTargetView(pBackBufferTexture, NULL, &pRenderTargetView);

	if (FAILED(hr)) {
		MessageBox(NULL, "���� Ÿ�� �� ���� ����", "����", MB_OK);
		return false;
	}
	// ���� Ÿ�� �� ���ε�. ������ ���ο� ����.
	pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);

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