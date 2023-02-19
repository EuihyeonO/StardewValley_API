#pragma once
#include <list>
#include <map>
#include <vector>

#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineObject.h>

// ���� :
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
    /// ���͸� ����� �Լ�
    /// </summary>
    /// <typeparam name="ActorType"> GameEngineActor�� ��ӹ��� Ŭ���� Ÿ�� </typeparam>
    /// <param name="_Order"> Actor�� ������Ʈ ���� ���ڰ� �������� ���� ������Ʈ �˴ϴ�. </param>
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

        // ���� ���ο� ����
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

        // � 
        std::list<GameEngineActor*>& Group = Actors[_GroupIndex];
        Result.reserve(Group.size());

        for (GameEngineActor* ActorPtr : Group)
        {
            ConvertType* ConvertPtr = dynamic_cast<ConvertType*>(ActorPtr);

            if (nullptr == ConvertType)
            {
                MsgAssert("����Ʈ �Ҽ� ���� ��ȯ�Դϴ�.");
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

        // � 
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

    // ���� ���� �ٸ� ������ ��ü�ȴ�.
    virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;
    // ���� ���� ���ο� ���� ���̴� ������ �ɰŴ�.
    virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;

private:
    static bool IsDebugRender;

    float4 CameraPos = float4::Zero;

    static float4 TextOutStart;
    static std::vector<std::string> DebugTexts;

    // �������� �˾Ƽ��� �ȵ�����
    //std::list<Player*> Actors;
    //std::list<Monster*> Actors;
    //std::list<Background*> Actors;

    // �ϳ��� �ڷ������� ��� ȭ�鳻�� �����ϴ� �͵��� ǥ���Ҽ� �ְ� �˴ϴ�.
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

    // ���������� ����̱� ������ private���� �д�.
    void Release();
};

