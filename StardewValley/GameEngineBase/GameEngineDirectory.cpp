#include "GameEngineDirectory.h"
#include "GameEngineFile.h"
#include <GameEngineBase/GameEngineDebug.h>


GameEngineDirectory::GameEngineDirectory()
{
}

GameEngineDirectory::~GameEngineDirectory()
{
}
void GameEngineDirectory::MoveParentToDirectory(const std::string_view& _String)
{
    std::string MovePath = "\\";
    MovePath += _String;

    Path.MoveParentToChildPath(MovePath.c_str());
}

bool GameEngineDirectory::Move(const std::string_view& _String)
{
    std::string MovePath = "\\";
    MovePath += _String;
    return Path.Move(MovePath.c_str());
}

GameEnginePath GameEngineDirectory::GetPlusFileName(const std::string_view& _String)
{

    std::string PathString = Path.GetPathToString();
    PathString += "\\";
    PathString += _String;

    return GameEnginePath(PathString);
}

bool GameEngineDirectory::MoveParent()
{
    if (true == Path.IsRoot())
    {
        MsgAssert("루트 디렉토리는 부모디렉토리로 이동할수 없습니다.");
        return false;
    }

    Path.MoveParent();

    return true;
}

// .png
// png

std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string_view& _Ext)
{
    std::filesystem::directory_iterator DirIter(Path.Path);

    std::string Ext = _Ext.data();

    std::vector<GameEngineFile> Files;

    for (const std::filesystem::directory_entry& Entry : DirIter)
    {
        if (true == Entry.is_directory())
        {
            // 재귀를 돌리면 다 돌것이다.
            continue;
        }

        Files.push_back(GameEngineFile(Entry.path()));
    }

    return Files;
}