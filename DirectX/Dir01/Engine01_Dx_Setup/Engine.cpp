#include "Engine.h"


Engine::Engine(HINSTANCE hinstance)
	: DXApp(hinstance)
{ // 오류가 뜨면 부모클래스를 생성하여 상속해주면 된다. 위의 라인처럼.

}

Engine::~Engine()
{

}

bool Engine::Init()
{
	if (DXApp::Init() == false) {
		return false;
	}
	return true;
}

void Engine::Update()
{
}

void Engine::Render()
{
}
