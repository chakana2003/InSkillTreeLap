#include <Windows.h> // �����츦 �����ϱ� ���� �ʿ�
#include "Engine.h"

int WINAPI WinMain(
	HINSTANCE hinstnace, 
	HINSTANCE previnstance, // ���� ������ ȣȯ������ ����
	LPSTR lpCmdLine, 
	int nCmdLine) 
{
	// For Test.
	//MessageBox(NULL, "�׽�Ʈ â�Դϴ�.", "�׽�Ʈ", MB_YESNO);

	Engine engine(hinstnace);
	if (engine.Init() == false) {
		return 0;
	}

	// ���� ����.
	return engine.Run();
}