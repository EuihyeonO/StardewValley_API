#pragma once
#include <GameEngineCore/GameEngineResources.h>


class globalSound
{

public:

    void WalkSoundOn();
    void WalkSoundOff();
    void SoundInit();

    void WalkSoundOnOff(const std::string_view _LevelName);

	globalSound();
	~globalSound();

	globalSound(const globalSound& _Other) = delete;
	globalSound(globalSound&& _Other) noexcept = delete;
	globalSound& operator=(const globalSound& _Other) = delete;
	globalSound& operator=(globalSound&& _Other) noexcept = delete;

protected:

private:
    GameEngineSoundPlayer WalkSound;
};

