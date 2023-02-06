#include "GameEngineDirectory.h"
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