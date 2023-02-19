#pragma once
#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>
#include <string_view>

// 설명 :
// 이녀석 자체가 사운드 파일 역할도 합니다.
class GameEngineSound
{
public:
    static void SoundUpdate();

    GameEngineSound();
    ~GameEngineSound();

    // delete Function
    GameEngineSound(const GameEngineSound& _Other) = delete;
    GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
    GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
    GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

    void SoundLoad(const std::string_view& _Path);
    FMOD::Channel* Play();

protected:

private:
    FMOD::Sound* FMODSound = nullptr;

};

