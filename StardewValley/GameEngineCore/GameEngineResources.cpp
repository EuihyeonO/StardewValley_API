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
    // ���� ���ϴ� ������ ���ϴ� ���� ��Ȯ�ϰ� 
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
        MsgAssert("�̹� �ε��� �̹����� �� �ε��Ϸ��� �߽��ϴ�." + UpperName);
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
        MsgAssert("�ε����� ���� �̹����� ����Ϸ��� �߽��ϴ�" + UpperName);
        return nullptr;
    }

    return FindIter->second;
}