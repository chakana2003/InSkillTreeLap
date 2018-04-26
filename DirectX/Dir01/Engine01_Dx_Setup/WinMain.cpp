#include <Windows.h> // 윈도우를 생성하기 위해 필요
#include "Engine.h"

int WINAPI WinMain(
	HINSTANCE hinstnace, 
	HINSTANCE previnstance, // 과거 버전과 호환때문에 붙임
	LPSTR lpCmdLine, 
	int nCmdLine) 
{
	// For Test.
	//MessageBox(NULL, "테스트 창입니다.", "테스트", MB_YESNO);

	Engine engine(hinstnace);
	if (engine.Init() == false) {
		return 0;
	}

	// 엔진 실행.
	return engine.Run();
}