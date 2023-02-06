#pragma once
#include <string>
#include <string_view>

// Ό³Έν :
class GameEngineString
{
public:
	static std::string ToUpper(const std::string_view& _Str);

	// delete Function

protected:

private:
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;


};

