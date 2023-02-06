#pragma once
#include <chrono>
#include <Windows.h>

// �ð��� ��ų� �ϴ� ��ɵ��� ����մϴ�.
// �⺻������ �ð��� ��� ����� ���������� ������
// �������� C++ std�� �ֽű���� ũ�γ븦 �̿��Ұ̴ϴ�.
// �ð��� ��� ����� �⺻������ CPU�� ������ �� �ֽ��ϴ�.
// �� �ϵ��� os�� ���� �޾ƿͼ� �츮���� �˷��ִ� �����̴�.

// �׷��� �⺻������ �ð��� ��� ������ ǥ���ϰ� �˴ϴ�.
// ������ ����ϴ�. 

// ���� :
class GameEngineTime
{
public:
	static GameEngineTime GlobalTime;

	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

	void Reset();

	float TimeCheck();

	float GetFloatDeltaTime() 
	{
		return floatDeltaTime;
	}

protected:
	

private:
	__int64 Tick = 0;
	LARGE_INTEGER Prev = LARGE_INTEGER();
	LARGE_INTEGER Current = LARGE_INTEGER();
	LARGE_INTEGER Second = LARGE_INTEGER();
	double DoubleDeltaTime = 0.0;
	float floatDeltaTime = 0.0;
};

