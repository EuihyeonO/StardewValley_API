#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineDebug.h>

// 다른 lib나 dll을 사용하기 위한 전처리문을 여기 넣을것입니다.
// #pragma comment(lib, "GameEngineBase.lib");

// lib를 통해서 dll을 사용한다고 하는건.
// fmod.dll을 쓰겠다.
#ifdef _DEBUG
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#else
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

// FMOD는 자신들의 기능을 이용할수 있게 해주는 클래스의 포인터를 주고
FMOD::System* SoundSystem = nullptr;

class SoundSystemCreator
{
public:
    SoundSystemCreator()
    {
        FMOD::System_Create(&SoundSystem);

        if (nullptr == SoundSystem)
        {
            MsgAssert("사운드 초기화가 제대로 되지 않았습니다.");
        }

        if (FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
        {
            MsgAssert("사운드 시스템 이니셜라이즈에 실패했습니다.");
        }

    }

    ~SoundSystemCreator()
    {
        SoundSystem->release();
    }
};

SoundSystemCreator SoundInitObject = SoundSystemCreator();

void GameEngineSound::SoundUpdate()
{
    if (nullptr == SoundSystem)
    {
        MsgAssert("사운드 업데이트가 불가능합니다.");
        return;
    }

    SoundSystem->update();
}

GameEngineSound::GameEngineSound()
{
}

GameEngineSound::~GameEngineSound()
{
}

void GameEngineSound::SoundLoad(const std::string_view& _Path)
{
    if (FMOD_OK != SoundSystem->createSound(_Path.data(), FMOD_LOOP_NORMAL, nullptr, &FMODSound))
    {
        MsgAssert(std::string("사운드 로드에 실패했습니다.\n 경로 : ") + _Path.data());
    }

    return;
}

FMOD::Channel* GameEngineSound::Play()
{
    if (nullptr == FMODSound)
    {
        MsgAssert(std::string("FMODSound가 nullptr 입니다 "));
    }

    FMOD::Channel* Return;

    SoundSystem->playSound(FMODSound, nullptr, false, &Return);

    return Return;
}