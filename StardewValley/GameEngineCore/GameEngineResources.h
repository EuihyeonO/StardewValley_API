#pragma once

#include <map>
#include <string>
#include <GameEnginePlatform/GameEngineImage.h>

// 사운드 이미지 전부다 이녀석이 관리하겠습니다.

// 설명 :
class GameEnginePath;
class GameEngineImage;
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

    void Release();

protected:
    // 

private:
    static GameEngineResources Inst;

    GameEngineResources();
    ~GameEngineResources();

    //        xxxx.bmp
    std::map<std::string, GameEngineImage*> AllImage;

};

