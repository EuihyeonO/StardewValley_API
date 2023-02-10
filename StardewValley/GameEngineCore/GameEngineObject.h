#pragma once
#include <string>
#include <string_view>

// 설명 : 오브젝트 구조의 가장 기본이 되어주는 클래스.
class GameEngineObject
{
public:
    // constrcuter destructer
    GameEngineObject();
    virtual ~GameEngineObject();

    // delete Function
    GameEngineObject(const GameEngineObject& _Other) = delete;
    GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
    GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
    GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

    bool IsUpdate()
    {
        //         조건          ?              true 일때                                      :         false 일때
        // 부모가 있다면
        // ((true == ObjectUpdate && false == IsDeath()) && true == Parent->IsUpdate())
        // 내가 켜져있어야하고 true == ObjectUpdate
        // 내가 죽지도 않았어야 한다. false == IsDeath()
        // 부모도 켜져있어야 한다 true == Parent->IsUpdate()

        return nullptr != Parent ? ((true == ObjectUpdate && false == IsDeath()) && true == Parent->IsUpdate()) : (ObjectUpdate && false == IsDeath());

        // return nullptr != Parent ? 1000 : 200;
    }

    bool IsDeath()
    {
        return nullptr != Parent ? (true == ObjectDeath || Parent->IsDeath()) : (true == ObjectDeath);
    }

    void Death()
    {
        ObjectDeath = true;
    }

    void On()
    {
        ObjectUpdate = true;
    }
    void Off()
    {
        ObjectUpdate = false;
    }

    void OnOffSwtich()
    {
        ObjectUpdate = !ObjectUpdate;
    }

    virtual void SetOrder(int _Order)
    {
        Order = _Order;
    }

    int GetOrder()
    {
        return Order;
    }

    virtual void SetOwner(GameEngineObject* _Parent)
    {
        Parent = _Parent;
    }

    template<typename ConvertType>
    ConvertType* GetOwner()
    {
        return dynamic_cast<ConvertType*>(Parent);
    }

    GameEngineObject* GetOwner()
    {
        return Parent;
    }

    void SetName(const std::string_view& _View)
    {
        Name = _View;
    }

    const std::string& GetName()
    {
        return Name;
    }

    std::string GetNameCopy()
    {
        return Name;
    }

protected:

private:
    int Order;

    // 자기를 관리하거나 자기를 소유한 오브젝트들을 부모라는 느낌으로 보려고 하는것.
    GameEngineObject* Parent = nullptr;

    bool ObjectDeath = false;
    bool ObjectUpdate = true;

    std::string Name;

};

