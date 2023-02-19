#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "GameEngineLevel.h"
#include "GameEngineResources.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineBase/GameEngineTime.h>

GameEngineCore* Core;

GameEngineCore* GameEngineCore::GetInst()
{
    return Core;
}

void GameEngineCore::GlobalStart()
{
    Core->Start();

    GameEngineTime::GlobalTime.Reset();
}

void GameEngineCore::GlobalUpdate()
{

    // ������ �����Ҷ� �ѹ� ��ŸŸ���� ���ϰ�
    GameEngineSound::SoundUpdate();
    float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck();
    GameEngineInput::Update(TimeDeltaTime);

    // ���⿡�� ó���Ѵ�
    if (nullptr != Core->NextLevel)
    {
        GameEngineLevel* PrevLevel = Core->MainLevel;
        GameEngineLevel* NextLevel = Core->NextLevel;

        if (nullptr != PrevLevel)
        {
            PrevLevel->LevelChangeEnd(NextLevel);
            PrevLevel->ActorLevelChangeEnd(NextLevel);
        }

        Core->MainLevel = NextLevel;
        Core->NextLevel = nullptr;

        if (nullptr != NextLevel)
        {
            NextLevel->LevelChangeStart(PrevLevel);
            NextLevel->ActorLevelChangeStart(PrevLevel);
        }
    }

    if (1.0f / 60.0f <= TimeDeltaTime)
    {
        TimeDeltaTime = 1.0f / 60.0f;
    }

    Core->Update();
    if (nullptr == Core->MainLevel)
    {
        MsgAssert("������ ���������� ���� ���·� �ھ �����߽��ϴ�");
        return;
    }

    Core->MainLevel->Update(TimeDeltaTime);
    Core->MainLevel->ActorsUpdate(TimeDeltaTime);
    GameEngineWindow::DoubleBufferClear();
    Core->MainLevel->ActorsRender(TimeDeltaTime);
    GameEngineWindow::DoubleBufferRender();
    Core->MainLevel->Release();
}

void GameEngineCore::GlobalEnd()
{
    Core->End();

    GameEngineResources::GetInst().Release();
}


GameEngineCore::GameEngineCore()
{
    GameEngineDebug::LeakCheck();
    // ���� �ڽ��߿� �ϳ��ϼ��ۿ� ����.
    // ���� ���븸������� ���� �����̴�.
    Core = this;
}

GameEngineCore::~GameEngineCore()
{
    std::map<std::string, GameEngineLevel*>::iterator StartIter = Levels.begin();
    std::map<std::string, GameEngineLevel*>::iterator EndIter = Levels.end();

    for (size_t i = 0; StartIter != EndIter; ++StartIter)
    {
        if (nullptr != StartIter->second)
        {
            delete StartIter->second;
        }
    }

    Levels.clear();
}

void GameEngineCore::CoreStart(HINSTANCE _instance)
{
    if (false == GameEngineInput::IsKey("EngineMouseLeft"))
    {
        GameEngineInput::CreateKey("EngineMouseLeft", VK_LBUTTON);
        GameEngineInput::CreateKey("EngineMouseRight", VK_RBUTTON);
    }

    GameEngineWindow::WindowCreate(_instance, "MainWindow", { 1280, 720 }, { 0, 0 });
    GameEngineWindow::WindowLoop(GameEngineCore::GlobalStart, GameEngineCore::GlobalUpdate, GameEngineCore::GlobalEnd);
}

void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
    std::map<std::string, GameEngineLevel*>::iterator FindIter = Levels.find(_Name.data());

    if (FindIter == Levels.end())
    {
        std::string Name = _Name.data();
        MsgAssert(Name + "�������� �ʴ� ������ �����Ű���� �߽��ϴ�");
        return;
    }

    NextLevel = FindIter->second;
}

void GameEngineCore::LevelLoading(GameEngineLevel* _Level, const std::string_view& _Name)
{
    if (nullptr == _Level)
    {
        MsgAssert("nullptr �� ������ �ε��Ϸ��� �߽��ϴ�.");
        return;
    }

    _Level->SetName(_Name);
    _Level->Loading();
}