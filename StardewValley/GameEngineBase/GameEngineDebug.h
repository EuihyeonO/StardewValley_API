#pragma once
#include <Windows.h>
#include <assert.h>
#include <string>

// Ό³Έν :
class GameEngineDebug
{
public:

	// delete Function
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;

	static void LeakCheck();

protected:

private:
	// constrcuter destructer
	GameEngineDebug();
	~GameEngineDebug();

};


#define MsgAssert(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK); assert(false);