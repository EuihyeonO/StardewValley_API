#pragma once

#include <map>
#include <string>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineSound.h>

// 사운드 이미지 전부다 이녀석이 관리하겠습니다.

class GameEngineSoundPlayer
{
public:
    GameEngineSoundPlayer() {}
    GameEngineSoundPlayer(FMOD::Channel* _Channel);

    void LoopCount(int _Count);
    void Volume(float _Volume);
    void Stop();

private:
    FMOD::Channel* ControlChannel = nullptr;

};

// 설명 :
class GameEnginePath;
class GameEngineImage;
class GameEngineSound;
class GameEngineResources
{
public:
    GameEngineResources(const GameEngineResources& _Other) = delete;
    GameEngineResources(GameEngineResources&& _Other) noexcept = delete;
    GameEngineResources& operator=(const GameEngineResources& _Other) = delete;
    GameEngineResources& operator=(GameEngineResources&& _Other) noexcept = delete;

    static GameEngineResources& GetInst()
    {
        return Inst;
    }

    GameEngineImage* ImageLoad(const GameEnginePath& _Path);

    GameEngineImage* ImageLoad(const std::string_view& _Path, const std::string_view& _Name);

    GameEngineImage* ImageFind(const std::string_view& _Name);

    GameEngineSound* SoundLoad(const GameEnginePath& _Path);

    GameEngineSound* SoundLoad(const std::string_view& _Path, const std::string_view& _Name);

    GameEngineSound* SoundFind(const std::string_view& _Name);

    void SoundPlay(const std::string_view& _Name);

    GameEngineSoundPlayer SoundPlayToControl(const std::string_view& _Name);

    void Release();

protected:
    // 

private:
    static GameEngineResources Inst;

    GameEngineResources();
    ~GameEngineResources();

    //        xxxx.bmp
    std::map<std::string, GameEngineImage*> AllImage;
    std::map<std::string, GameEngineSound*> AllSound;

};

