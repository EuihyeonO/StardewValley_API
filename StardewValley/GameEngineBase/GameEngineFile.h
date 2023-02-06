#pragma once

// Ό³Έν :
class GameEngineFile
{
public:
	// constrcuter destructer
	GameEngineFile();
	~GameEngineFile();

	// delete Function
	GameEngineFile(const GameEngineFile& _Other) = delete;
	GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;

protected:

private:

};

