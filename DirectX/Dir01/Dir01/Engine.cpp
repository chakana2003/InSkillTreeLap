#include "Engine.h"


Engine::Engine(HINSTANCE hinstance)
	: DXApp(hinstance)
{ // ������ �߸� �θ�Ŭ������ �����Ͽ� ������ָ� �ȴ�. ���� ����ó��.

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
	float color[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	
}
