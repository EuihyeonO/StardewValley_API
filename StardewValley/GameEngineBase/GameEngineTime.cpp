#include "GameEngineTime.h"

GameEngineTime GameEngineTime::GlobalTime;

GameEngineTime::GameEngineTime() 
{
	// 1�ʸ� ���������� ���� �����Դϴ�. 
	// �����Ҷ� 1���� ���ϸ� �ȴ�.
	QueryPerformanceFrequency(&Second);
	QueryPerformanceCounter(&Prev);
}

GameEngineTime::~GameEngineTime() 
{
}
//
//void GameEngineTime::TimeCheckStart() 
//{
//	// 0�� 0�� 0�� 0��
//
//	// ���� �� �Լ��� ��������� ���� �ð����� �� �Լ��� ������ ���������� ������ ��Ÿ�� ����.
//	// ��ǻ�Ͱ� ����ִ� �׶����� �� �ð�.
//	// 100�� ���Ծ��.
//	// QueryPerformanceCounter(&Prev);
//
//	// 1�ʸ� 200���� ǥ���Ҽ� �ִ�.
//
//		//QueryPerformanceCounter()
//
//	// �������� �ð��� �� �غ� �Ҳ�
//}


void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev);
}

float GameEngineTime::TimeCheck()
{
	// �׷��� �� �Լ��� ����ɶ����� �ɸ� �ð���....

	QueryPerformanceCounter(&Current);

	Tick = Current.QuadPart - Prev.QuadPart;

	// ����ð��� ��������?
	//                          200                               100                                              100
	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart);

	Prev.QuadPart = Current.QuadPart;

	floatDeltaTime = static_cast<float>(DoubleDeltaTime);

	return floatDeltaTime;
}
