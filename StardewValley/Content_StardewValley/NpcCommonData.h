#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <string_view>

class GameEngineRender;
class GameEngineCollision;

class NpcCommonData : public GameEngineActor
{

public:
    void SetBodyRender(const std::string_view& _ImageName, float4 _pos);
    void SetCollision();
    void RenderOrderUpdate();

	NpcCommonData();
	~NpcCommonData();

	NpcCommonData(const NpcCommonData& _Other) = delete;
	NpcCommonData(NpcCommonData&& _Other) noexcept = delete;
	NpcCommonData& operator=(const NpcCommonData& _Other) = delete;
	NpcCommonData& operator=(NpcCommonData&& _Other) noexcept = delete;

protected:

private:
    GameEngineRender* BodyRender = nullptr;

    GameEngineCollision* BodyCollision = nullptr;
    GameEngineCollision* OrderCollision = nullptr;
};

