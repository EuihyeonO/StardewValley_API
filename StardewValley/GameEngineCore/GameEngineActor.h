#pragma once
// std
#include <list>
#include <string_view>
// 플랫폼
#include <Windows.h>
// User
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

// 화면에 존재하고 위치가 있어야하는 모든것들의 기본기능을 지원해줄 겁니다.
// 그려져야 한다.

// 설명 :
class GameEngineLevel;
class GameEngineRender;
class GameEngineCollision;
class GameEngineActor : public GameEngineObject
{
    friend GameEngineLevel;

public:
    // constrcuter destructer
    GameEngineActor();
    ~GameEngineActor();

    // delete Function
    GameEngineActor(const GameEngineActor& _Other) = delete;
    GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
    GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
    GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

    inline float4 GetPos()
    {
        return Pos;
    }

    inline void SetPos(const float4& _MovePos)
    {
        Pos = _MovePos;
    }

    inline void SetMove(const float4& _MovePos)
    {
        Pos += _MovePos;
    }

    GameEngineLevel* GetLevel();

#pragma region CreateRenderEnumOverLoadings

    template<typename EnumType>
    GameEngineRender* CreateRender(const std::string_view& _Image, EnumType _Order)
    {
        return CreateRender(_Image, static_cast<int>(_Order));
    }

    template<typename EnumType>
    GameEngineRender* CreateRender(EnumType _Order)
    {
        return CreateRender(static_cast<int>(_Order));
    }

#pragma endregion

    GameEngineRender* CreateRender(const std::string_view& _Image, int _Order = 0);
    GameEngineRender* CreateRender(int _Order = 0);

    template<typename EnumType>
    GameEngineCollision* CreateCollision(EnumType _GroupIndex)
    {
        return CreateCollision(static_cast<int>(_GroupIndex));
    }

    GameEngineCollision* CreateCollision(int _GroupIndex = 0);

protected:
    // 안구현할수도 있다.
    // ex) 나무는 Update를 안구현할수도 있다.

    // 시작하기전에 뭔가 준비해야할것이 있으면 여기서 해라.
    virtual void Start() {}

    // 키입력을 받거나 인공지능을 점수를 계산하거나 하는 것들을 여기서 처리
    virtual void Update(float _DeltaTime) {}

    // 순서를 제어 함수를 한번 더실행하고 
    virtual void LateUpdate(float _DeltaTime) {}

    // 화면에 그려지는 기능들을 여기서 처리
    virtual void Render(float _DeltaTime) {}

    // 
    inline float GetLiveTime()
    {
        return LiveTime;
    }

    virtual void LevelChangeEnd(GameEngineLevel* _PrevLevel);
    virtual void LevelChangeStart(GameEngineLevel* _PrevLevel);

private:
    float LiveTime = 0.0;
    float4 Pos = { 0.0f, 0.0f };
    std::list<GameEngineRender*> RenderList;
    std::list<GameEngineCollision*> CollisionList;

    void Release();
};

