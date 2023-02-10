#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineDebug.h>

// �ٸ� lib�� dll�� ����ϱ� ���� ��ó������ ���� �������Դϴ�.
// #pragma comment(lib, "GameEngineBase.lib");

// lib�� ���ؼ� dll�� ����Ѵٰ� �ϴ°�.
// fmod.dll�� ���ڴ�.
#ifdef _DEBUG
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#else
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

// FMOD�� �ڽŵ��� ����� �̿��Ҽ� �ְ� ���ִ� Ŭ������ �����͸� �ְ�
FMOD::System* SoundSystem = nullptr;

class SoundSystemCreator
{
public:
    SoundSystemCreator()
    {
        FMOD::System_Create(&SoundSystem);

        if (nullptr == SoundSystem)
        {
            MsgAssert("���� �ʱ�ȭ�� ����� ���� �ʾҽ��ϴ�.");
        }

        if (FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
        {
            MsgAssert("���� �ý��� �̴ϼȶ���� �����߽��ϴ�.");
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
        MsgAssert("���� ������Ʈ�� �Ұ����մϴ�.");
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
        MsgAssert(std::string("���� �ε忡 �����߽��ϴ�.\n ��� : ") + _Path.data());
    }

    return;
}

FMOD::Channel* GameEngineSound::Play()
{
    if (nullptr == FMODSound)
    {
        MsgAssert(std::string("FMODSound�� nullptr �Դϴ� "));
    }

    FMOD::Channel* Return;

    SoundSystem->playSound(FMODSound, nullptr, false, &Return);

    return Return;
}