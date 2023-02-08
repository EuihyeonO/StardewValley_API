#pragma once
#include <GameEngineBase/GameEngineMath.h>

class LevelMap
{

public:
    float4 GetMapSize()
    {
        return Mapsize;
    }

	LevelMap();
	~LevelMap();

	LevelMap(const LevelMap& _Other) = delete;
	LevelMap(LevelMap&& _Other) noexcept = delete;
	LevelMap& operator=(const LevelMap& _Other) = delete;
	LevelMap& operator=(LevelMap&& _Other) noexcept = delete;

protected:

private:
    float4 Mapsize = { 0,0 };
};

