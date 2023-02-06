#pragma once
// c++�� ����Ǵ� ������ ����Ҽ� �ִ� ��� ���ڿ� ���� ó������� �������ش�.
#include <filesystem>

// ���� : ��ο� ���õ� ����� ��ǥ�ϴ� Ŭ����
class GameEnginePath
{
public:
	// constrcuter destructer
	GameEnginePath();
	GameEnginePath(std::filesystem::path _Path);
	GameEnginePath(const std::string& _Path);
	~GameEnginePath();

	// delete Function
	GameEnginePath(const GameEnginePath& _Other);
	GameEnginePath(GameEnginePath&& _Other);
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	std::string GetFileName() const;
	std::string GetPathToString() const;

	void MoveParent();

	// ���ڽ��� Ư�� ��γ� Ư�� ������ �ִ°����� �ڵ� move
	void MoveParentToChildPath(const std::string_view& _String);

	bool IsExists();
	bool IsExistsToPlusString(const std::string_view& _String);

	// bool MoveParentToChildPath(const std::string_view& _IOName );

	bool IsRoot();

	bool Move(const std::string_view& _Path);

	void SetPath(const std::string_view& _Path);


protected:

private:
	// �������ؼ� ������ �ʰ� �Ǿ����ϴ�.
	// std::string Path;
	std::filesystem::path Path;

};

