#pragma once
#include <GameEngineCore/GameEngineResources.h>


class globalSound
{

public:
    static globalSound* GetSoundPlayer()
    {
        return globalSoundPlayer;
    }

    void SoundInit();
    void WalkSoundOff();

    void WalkSoundOn();
    
    void SoundUpdate(const std::string_view _LevelName);

    void BGM_On(const std::string_view _LevelName);

	globalSound();
	~globalSound();

	globalSound(const globalSound& _Other) = delete;
	globalSound(globalSound&& _Other) noexcept = delete;
	globalSound& operator=(const globalSound& _Other) = delete;
	globalSound& operator=(globalSound&& _Other) noexcept = delete;

protected:

private:
    static globalSound* globalSoundPlayer;

    GameEngineSoundPlayer WalkSound;

    GameEngineSoundPlayer Farm_BGM;
    GameEngineSoundPlayer Title_BGM;
    GameEngineSoundPlayer Mine_BGM;

    float Volume = 1;
    float MineVolume = 0;
    float FarmVolume = 0;
};

