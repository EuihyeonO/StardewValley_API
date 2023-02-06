#include "GameEngineInput.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>

std::map<std::string, GameEngineInput::GameEngineKey> GameEngineInput::Keys;
bool GameEngineInput::IsAnyKeyValue = false;

void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
    if (true == KeyCheck())
    {
        PressTime += _DeltaTime;
        if (true == Free)
        {
            Down = true;
            Press = true;
            Up = false;
            Free = false;
        }
        else if (true == Down)
        {
            Down = false;
            Press = true;
            Up = false;
            Free = false;
        }
    }
    else
    {
        PressTime = 0.0f;
        if (true == Press)
        {
            Down = false;
            Press = false;
            Up = true;
            Free = true;
        }
        else if (true == Up)
        {
            Down = false;
            Press = false;
            Up = false;
            Free = true;
        }
    }
}

bool GameEngineInput::IsDown(const std::string_view& _Name)
{
    std::string UpperName = GameEngineString::ToUpper(_Name);

    if (Keys.end() == Keys.find(UpperName))
    {
        MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
    }


    return Keys[UpperName].Down;
}
bool GameEngineInput::IsUp(const std::string_view& _Name)
{
    std::string UpperName = GameEngineString::ToUpper(_Name);

    if (Keys.end() == Keys.find(UpperName))
    {
        MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
    }


    return Keys[UpperName].Up;
}
bool GameEngineInput::IsPress(const std::string_view& _Name)
{
    std::string UpperName = GameEngineString::ToUpper(_Name);

    if (Keys.end() == Keys.find(UpperName))
    {
        MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
    }


    return Keys[UpperName].Press;
}
bool GameEngineInput::IsFree(const std::string_view& _Name)
{
    std::string UpperName = GameEngineString::ToUpper(_Name);

    if (Keys.end() == Keys.find(UpperName))
    {
        MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
    }

    return Keys[UpperName].Free;
}

float GameEngineInput::GetPressTime(const std::string_view& _Name)
{
    std::string UpperName = GameEngineString::ToUpper(_Name);

    if (Keys.end() == Keys.find(UpperName))
    {
        MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
    }

    return Keys[UpperName].PressTime;
}

bool GameEngineInput::IsKey(const std::string_view& _Name)
{
    std::string UpperName = GameEngineString::ToUpper(_Name);

    return Keys.end() != Keys.find(UpperName);
}

void GameEngineInput::CreateKey(const std::string_view& _Name, int _Key)
{
    std::string UpperName = GameEngineString::ToUpper(_Name);

    if (Keys.end() != Keys.find(UpperName))
    {
        MsgAssert("�̹� �����ϴ� �̸��� ũ�⸦ �� ������� �߽��ϴ�.");
    }

    _Key = toupper(_Key);

    Keys[UpperName].Key = _Key;
}

/// GameEngineInput
GameEngineInput::GameEngineInput()
{
}

GameEngineInput::~GameEngineInput()
{
}

void GameEngineInput::Update(float _DeltaTime)
{
    std::map<std::string, GameEngineKey>::iterator StartKeyIter = Keys.begin();
    std::map<std::string, GameEngineKey>::iterator EndKeyIter = Keys.end();

    for (; StartKeyIter != EndKeyIter; ++StartKeyIter)
    {
        StartKeyIter->second.Update(_DeltaTime);
    }
}