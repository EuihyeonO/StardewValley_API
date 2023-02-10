#pragma once
#include <Windows.h>
#include <map>
#include <string_view>
#include <GameEngineBase/GameEngineDebug.h>

// core�� ������ ��������ٰ� ���������� �����̴ϴ�.

// ���� : �������� ���� �ε��ؾ��� �ʼ����� ���ҽ��� 
// ���������Լ��� �����ϱ� �߻�Ŭ���̴�.
class GameEngineLevel;
class GameEngineCore
{
private:

    static void GlobalStart();
    static void GlobalUpdate();
    static void GlobalEnd();

public:
    // constrcuter destructer

    GameEngineCore();
    ~GameEngineCore();

    // delete Function
    GameEngineCore(const GameEngineCore& _Other) = delete;
    GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
    GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
    GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

    void CoreStart(HINSTANCE _instance);

    void ChangeLevel(const std::string_view& _Name);

    static GameEngineCore* GetInst();

    void DebugSwitch()
    {
        IsDebugValue = !IsDebugValue;
    }

    void SetDebugMode(bool _IsDebug)
    {
        IsDebugValue = _IsDebug;
    }

    bool IsDebug()
    {
        return IsDebugValue;
    }

protected:
    template<typename LevelType>
    void CreateLevel(const std::string_view& _Name)
    {
        // Title�� ������µ�
        // �� Title�� ����ڴٰ� �� ��Ȳ
        if (Levels.end() != Levels.find(_Name.data()))
        {
            std::string Name = _Name.data();
            MsgAssert(Name + "�̹� �����ϴ� �̸��� ������ ������� �߽��ϴ�");
            return;
        }

        // ��ĳ������ ��������?
        GameEngineLevel* Level = new LevelType();
        LevelLoading(Level, _Name);
        // Level->Loading();
        // insert�Ҷ����� ���ο� string�� ����鼭 �ڽŸ��� �޸𸮸� ������ �˴ϴ�.
        Levels.insert(std::make_pair(_Name.data(), Level));
    }

    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void End() = 0;

private:
    // �׷��� map�� ����Ѵ�. 
    // �����̶�°��� ����Դϴ�.
    // GameEngineLevel�� "��� �̸�"���� ã�� �̸����� �����Ű��.
    std::map<std::string, GameEngineLevel*> Levels;

    GameEngineLevel* NextLevel = nullptr;

    GameEngineLevel* MainLevel = nullptr;

    void LevelLoading(GameEngineLevel* _Level, const std::string_view& _Name);

    bool IsDebugValue = false;

};

