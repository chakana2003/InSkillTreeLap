#include "GameTimer.h"



GameTimer::GameTimer()
{
}


GameTimer::~GameTimer()
{
}

void GameTimer::StartTimer()
{
	LARGE_INTEGER frequencyCount;

	// WIN 32 API.
	QueryPerformanceFrequency(&frequencyCount);

	countsPerSecond = double(frequencyCount.QuadPart);

	// ƽ ������ �ð�.
	QueryPerformanceCounter(&frequencyCount);
	countStart = frequencyCount.QuadPart;
}

double GameTimer::GetTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	double time = (double)((currentTime.QuadPart - countStart) / countsPerSecond);
	return time;
}

double GameTimer::DeltaTime()
{
	// ƽ ������ ���� �ð� ���.
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	// ���� �����ӿ��� ���� �����ӱ��� ƽ ������ �󸶳� ���� �������� ���.
	__int64 tickCount = currentTime.QuadPart - prevFrameTimer;

	// ���� ������ �ð� ����.
	prevFrameTimer = currentTime.QuadPart;

	// ����ó��
	if (tickCount < 0.f)
		tickCount = 0.f;

	// ������ �ð��� �ʴ� �ð� ������ ��ȯ.
	double deltaTime = (double)(tickCount / countsPerSecond);
	if (deltaTime < 0.f)
		deltaTime = 0.f;

	return deltaTime;
}

void GameTimer::UpdateTimer()
{
	// ƽ ������ ������ �� ������Ű��.
	++frameCount;
	// �ð� ����ؼ� 1�� ������ Ÿ�̸� �ʱ�ȭ.
	if (GetTime() > 1.0f) {
		Reset();
	}
}

void GameTimer::Reset()
{
	fps = frameCount;
	frameCount = 0;
	StartTimer();
}

int GameTimer::GetFPS()
{
	return fps;
}
