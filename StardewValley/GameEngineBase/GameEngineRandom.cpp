#include "GameEngineRandom.h"
#include <chrono>


GameEngineRandom GameEngineRandom::MainRandom;

GameEngineRandom::GameEngineRandom()
    : MtGen(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
{

    // 34789312789312789321

    // ũ�γ�� std���� �����ϴ� �ð��� ������� �Լ��̴�.

}

GameEngineRandom::~GameEngineRandom()
{
}

