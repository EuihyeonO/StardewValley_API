#pragma once
#include <GameEngineCore/GameEngineResources.h>


class globalSound
{

public:

    void SoundInit();
    void SoundOff();

    void ToolSoundOn();
    void WalkSoundOn(const std::string_view _LevelName);
    
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
    GameEngineSoundPlayer WalkSound;

    GameEngineSoundPlayer Farm_BGM;

    GameEngineSoundPlayer AxeSound;
    GameEngineSoundPlayer HoeSound;
    GameEngineSoundPlayer PickSound;
    GameEngineSoundPlayer WateringSound;
};

