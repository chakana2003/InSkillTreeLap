#pragma once
#include <Windows.h>

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

protected:
	// Win32 �޼ҵ�.
	// ������ �ʱ�ȭ �Լ�. ( �ּ� �������� . �� ������ �����Ͻ� ����Ʈ�� �� �ڵ�� ���̴� ��찡 ����.)
	bool InitWindow();
};

