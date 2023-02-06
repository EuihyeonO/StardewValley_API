#include "GameEnginePath.h"
#include <Windows.h>
#include <io.h>
#include <GameEngineBase/GameEngineDebug.h>

GameEnginePath::GameEnginePath() 
	: Path(std::filesystem::current_path())
{
}

GameEnginePath::GameEnginePath(std::filesystem::path _Path)
	: Path(_Path)
{
}

GameEnginePath::GameEnginePath(const std::string& _Path)
	: Path(_Path)
{

}

GameEnginePath::GameEnginePath(GameEnginePath&& _Other)
	: Path(_Other.Path)
{

}

GameEnginePath::~GameEnginePath() 
{
}

GameEnginePath::GameEnginePath(const GameEnginePath& _Other)
	: Path(_Other.Path)
{

}

std::string GameEnginePath::GetFileName() const
{
	return Path.filename().string();
}


std::string GameEnginePath::GetPathToString() const
{
	return Path.string();
}

void GameEnginePath::MoveParent() 
{
	Path = Path.parent_path();
}

void GameEnginePath::MoveParentToChildPath(const std::string_view& _String)
{
	while (false == IsRoot())
	{
		if (true == IsExistsToPlusString(_String))
		{
			return;
		}
		
		MoveParent();
	}

	MsgAssert("�̷� ��θ� �ڽ����� ���� �θ�� �������� �ʽ��ϴ�.");
}

bool GameEnginePath::Move(const std::string_view& _Path)
{
	Path += _Path;

	if (false == IsExists())
	{
		MsgAssert("�������� �ʴ� ��η� �̵��Ϸ��� �߽��ϴ�.");
		return false;
	}

	return true;
}

bool GameEnginePath::IsRoot()
{
	return Path.root_path() == Path;
}

bool GameEnginePath::IsExists()
{
	return 0 == _access(Path.string().c_str(), 0);
}

bool GameEnginePath::IsExistsToPlusString(const std::string_view& _String)
{
	std::string Str = GetPathToString() + _String.data();
	return 0 == _access(Str.c_str(), 0);
}

void GameEnginePath::SetPath(const std::string_view& _Path)
{
	Path = _Path.data();
}