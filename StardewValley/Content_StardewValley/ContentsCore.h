#pragma once
#include <GameEngineCore/GameEngineCore.h>

#include <map>
#include <string>
#include <vector>

class GameEngineCollision;
class ContentsCore : public GameEngineCore
{

public:

	static ContentsCore& GetCore()
	{
		return Core;
	}
    static std::string GetNextMap()
    {
        return NextMap;
    }
    static void SetNextMap(std::string _NextMap)
    {
        NextMap = _NextMap;
    }

    void MapChange();

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
    static std::string NextMap;
    
    int isSet = 0;
};

