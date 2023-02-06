#include "GameEngineResources.h"

#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineDebug.h>

GameEngineResources GameEngineResources::Inst;

GameEngineResources::GameEngineResources()
{
}

GameEngineResources::~GameEngineResources()
{
}

void GameEngineResources::Release()
{
    // 내가 원하는 시점에 원하는 순간 정확하게 
    for (std::pair<std::string, GameEngineImage*> Pair : AllImage)
    {
        if (nullptr == Pair.second)
        {
            continue;
        }
        delete Pair.second;
    }
    AllImage.clear();
}

GameEngineImage* GameEngineResources::ImageLoad(const GameEnginePath& _Path)
{
    return ImageLoad(_Path.GetPathToString().c_str(), _Path.GetFileName().c_str());
}

GameEngineImage* GameEngineResources::ImageLoad(const std::string_view& _Path, const std::string_view& _Name)
{
    // D:\\Project\\AR45\\WINAPI\\APIApp\\ContentsResources\\Image\\Heros.BmP

    std::string UpperName = GameEngineString::ToUpper(_Name);

    if (AllImage.end() != AllImage.find(UpperName))
    {
        MsgAssert("이미 로드한 이미지를 또 로드하려고 했습니다." + UpperName);
        return nullptr;
    }

    GameEngineImage* NewImage = new GameEngineImage();
    NewImage->ImageLoad(_Path);
    AllImage.insert(std::make_pair(UpperName, NewImage));
    return NewImage;
}

GameEngineImage* GameEngineResources::ImageFind(const std::string_view& _Name)
{
    std::string UpperName = GameEngineString::ToUpper(_Name);

    std::map<std::string, GameEngineImage*>::iterator FindIter = AllImage.find(UpperName);

    if (AllImage.end() == FindIter)
    {
        MsgAssert("로드하지 않은 이미지를 사용하려고 했습니다" + UpperName);
        return nullptr;
    }

    return FindIter->second;
}