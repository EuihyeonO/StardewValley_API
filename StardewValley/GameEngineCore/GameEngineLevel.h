#pragma once
#include <list>
#include <map>
#include <vector>

#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineObject.h>

// 설명 :
class GameEngineCore;
class GameEngineActor;
class GameEngineRender;
class GameEngineCollision;
class GameEngineLevel : public GameEngineObject
{
    friend GameEngineCore;
    friend GameEngineRender;
    friend GameEngineCollision;

public:
    // constrcuter destructer
    GameEngineLevel();
    virtual ~GameEngineLevel() = 0;

    // delete Function
    GameEngineLevel(const GameEngineLevel& _Other) = delete;
    GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
    GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
    GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

    static void DebugRenderSwitch()
    {
        IsDebugRender = !IsDebugRender;
    }

    float4 GetMousePos();
    float4 GetMousePosToCamera();

    /// <summary>
    /// 액터를 만드는 함수
    /// </summary>
    /// <typeparam name="ActorType"> GameEngineActor를 상속받은 클래스 타입 </typeparam>
    /// <param name="_Order"> Actor의 업데이트 순서 숫자가 작을수록 먼저 업데이트 됩니다. </param>
    template<typename ActorType, typename EnumType>
    ActorType* CreateActor(EnumType _Order)
    {
        return CreateActor<ActorType>(static_cast<int>(_Order));
    }

    template<typename ActorType>
    ActorType* CreateActor(int _Order = 0)
    {
        //if (Actors.end() == Actors.find(_Order))
        //{
        //	Actors.insert(std::make_pair(_Order, std::list<GameEngineActor*>()));
        //}

        GameEngineActor* Actor = new ActorType();

        ActorStart(Actor, _Order);

        // 맵의 새로운 문법
        Actors[_Order].push_back(Actor);

        return dynamic_cast<ActorType*>(Actor);
    }

    void SetCameraMove(const float4& _MoveValue)
    {
        CameraPos += _MoveValue;
    }

    void SetCameraPos(const float4& _CameraPos)
    {
        CameraPos = _CameraPos;
    }

    float4 GetCameraPos()
    {
        return CameraPos;
    }

    template<typename ConvertType>
    std::vector<ConvertType*> GetConvertActors(int _GroupIndex)
    {
        std::vector<ConvertType*> Result;

        // 어떤 
        std::list<GameEngineActor*>& Group = Actors[_GroupIndex];
        Result.reserve(Group.size());

        for (GameEngineActor* ActorPtr : Group)
        {
            ConvertType* ConvertPtr = dynamic_cast<ConvertType*>(ActorPtr);

            if (nullptr == ConvertType)
            {
                MsgAssert("컨버트 할수 없는 변환입니다.");
            }

            Result.push_back(ConvertPtr);
        }

        return Result;
    }

    template<typename EnumType>
    std::vector<GameEngineActor*> GetActors(EnumType _GroupIndex)
    {
        return GetActors(static_cast<int>(_GroupIndex));
    }

    std::vector<GameEngineActor*> GetActors(int _GroupIndex)
    {
        std::vector<GameEngineActor*> Result;

        // 어떤 
        std::list<GameEngineActor*>& Group = Actors[_GroupIndex];
        Result.reserve(Group.size());

        for (GameEngineActor* ActorPtr : Group)
        {
            Result.push_back(ActorPtr);
        }

        return Result;
    }

    static void DebugTextPush(const std::string& _DebugText)
    {
        DebugTexts.push_back(_DebugText);
    }

protected:
    virtual void Loading() = 0;
    virtual void Update(float _DeltaTime) = 0;

    // 내가 이제 다른 레벨로 교체된다.
    virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;
    // 내가 이제 새로운 눈에 보이는 레벨이 될거다.
    virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;

private:
    static bool IsDebugRender;

    float4 CameraPos = float4::Zero;

    static float4 TextOutStart;
    static std::vector<std::string> DebugTexts;

    // 컨텐츠를 알아서도 안되지만
    //std::list<Player*> Actors;
    //std::list<Monster*> Actors;
    //std::list<Background*> Actors;

    // 하나의 자료형으로 모든 화면내에 등장하는 것들을 표현할수 있게 됩니다.
    // 
    std::map<int, std::list<GameEngineActor*>> Actors;

    void ActorsUpdate(float _DeltaTime);
    void ActorsRender(float _DeltaTime);
    void ActorLevelChangeEnd(GameEngineLevel* _NextLevel);
    void ActorLevelChangeStart(GameEngineLevel* _PrevLevel);


    void ActorStart(GameEngineActor* _Actor, int _Order);

    std::map<int, std::list<GameEngineRender*>> Renders;
    void PushRender(GameEngineRender* _Render, int _ChangeOrder);

    std::map<int, std::list<GameEngineCollision*>> Collisions;
    void PushCollision(GameEngineCollision* _Collision, int _ChangeOrder);

    // 엔진수준의 기능이기 때문에 private으로 둔다.
    void Release();
};

