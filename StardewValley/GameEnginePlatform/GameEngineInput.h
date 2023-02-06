#pragma once
#include <Windows.h>
#include <map>
#include <string>

// ���� :
class GameEngineWindow;
class GameEngineInput
{
    friend GameEngineWindow;

private:
    class GameEngineKey
    {
        friend GameEngineInput;

        bool Down = false; // ���� �Ѽ���
        bool Press = false; // ��� ������ �ִ�.
        bool Up = false; // �� �Ѽ���
        bool Free = true; // �ȴ����� �ִ�.

        float PressTime; // ���ʰ� ������.
        int Key = -1;

        bool KeyCheck()
        {
            return 0 != GetAsyncKeyState(Key);
        }

        void Update(float _DeltaTime);
    };

public:

    // delete Function
    GameEngineInput(const GameEngineInput& _Other) = delete;
    GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
    GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
    GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

    static void Update(float _DeltaTime);

    static void CreateKey(const std::string_view& _Name, int _Key);

    static bool IsKey(const std::string_view& _Name);

    static bool IsDown(const std::string_view& _Name);
    static bool IsUp(const std::string_view& _Name);
    static bool IsPress(const std::string_view& _Name);
    static bool IsFree(const std::string_view& _Name);
    static float GetPressTime(const std::string_view& _Name);

    static bool IsAnyKey()
    {
        return IsAnyKeyValue;
    }

protected:

private:
    // constrcuter destructer
    GameEngineInput();
    ~GameEngineInput();

    //      PlayerJump       A
    static std::map<std::string, GameEngineKey> Keys;
    static bool IsAnyKeyValue;

    static void IsAnyKeyOn()
    {
        IsAnyKeyValue = true;
    }

    static void IsAnyKeyOff()
    {
        IsAnyKeyValue = false;
    }
};


