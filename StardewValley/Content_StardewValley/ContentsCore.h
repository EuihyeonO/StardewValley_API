#pragma once
#include <GameEngineCore/GameEngineCore.h>

class ContentsCore : public GameEngineCore
{

public:

	static ContentsCore& GetCore()
	{
		return Core;
	}

	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void End() override;
private:
	ContentsCore();
	~ContentsCore();

	static ContentsCore Core;
};

