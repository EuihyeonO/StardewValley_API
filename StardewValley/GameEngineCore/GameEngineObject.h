#pragma once
#include <string>
#include <string_view>

// ���� : ������Ʈ ������ ���� �⺻�� �Ǿ��ִ� Ŭ����.
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
        //         ����          ?              true �϶�                                      :         false �϶�
        // �θ� �ִٸ�
        // ((true == ObjectUpdate && false == IsDeath()) && true == Parent->IsUpdate())
        // ���� �����־���ϰ� true == ObjectUpdate
        // ���� ������ �ʾҾ�� �Ѵ�. false == IsDeath()
        // �θ� �����־�� �Ѵ� true == Parent->IsUpdate()

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

    // �ڱ⸦ �����ϰų� �ڱ⸦ ������ ������Ʈ���� �θ��� �������� ������ �ϴ°�.
    GameEngineObject* Parent = nullptr;

    bool ObjectDeath = false;
    bool ObjectUpdate = true;

    std::string Name;

};

