#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <D3DX11.h>

class DXApp
{
public:

public:
	DXApp(HINSTANCE hinstance);
	virtual ~DXApp();

	// ���� �޼��� ����.
	int Run();

	// ������ ��ũ �޼ҵ�.
	virtual bool Init();
	virtual void Update() = 0;    // ��ӹ޴� Ŭ������ �ݵ�� �������־���ϴ� �Լ��� ����ϴ� ���
	virtual void Render() = 0;
	virtual LRESULT MegProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);  // �����쿡�� �޼����� ������ �� �޼����� ���� �� �ִ� �ݹ��Լ�
	
protected:
	// Win32 ��� ����
	HWND hwnd;
	HINSTANCE hinstance;
	UINT clientWidth;
	UINT clientHeight;
	LPCSTR appTitle;   // â�� �̸��� �����ϴ� ���ڿ�
	DWORD wndStyle;  // �𸣸� F12 �� ������ ���Ǹ� Ÿ�� �ö󰡺���

	// ���̷�Ʈ X 11 ��� ����.
	ID3D11Device* pDevice;   // ������ ���� �ٸ� ���� ����.
	ID3D11DeviceContext* pDeviceContext;  // ������ ����.
	IDXGISwapChain* pSwapChain;     // ���� ü��.
	ID3D11RenderTargetView* pRenderTargetView;  // ���� Ÿ��.

protected:
	// Win32 �޼ҵ�.
	// ������ �ʱ�ȭ �Լ�. ( �ּ� �������� . �� ������ �����Ͻ� ����Ʈ�� �� �ڵ�� ���̴� ��찡 ����.)
	bool InitWindow();

	// ���̷�Ʈ X �ʱ�ȭ
	bool InitDirect3D();
};

