#include <GameEnginePlatform/GameEngineWindow.h>

#include "ContentsCore.h"
#include "Level_Title.h"
#include "Level_Farm.h"
#include "Level_Village.h"
#include "Level_House.h"
#include "globalValue.h"
#include <GameEnginePlatform/GameEngineInput.h>



ContentsCore ContentsCore::Core;
std::string ContentsCore::NextMap;

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
    if (GameEngineInput::IsKey("Debug") == false)
    {
        GameEngineInput::CreateKey("Debug", 'L');
    }

    GameEngineWindow::SettingWindowSize({1280, 768}); 
    GameEngineWindow::SettingWindowPos({277, 156}); 

    CreateLevel<Level_Title>("Title");
	CreateLevel<Level_Farm>("Farm");
	CreateLevel<Level_Village>("Village");
	CreateLevel<Level_House>("House");
	
	ChangeLevel("Farm");
}

void ContentsCore::Update()
{
    MapChange();
}

void ContentsCore::End()
{
}

void ContentsCore::MapChange()
{
    if (NextMap == "House")
    {
        ChangeLevel("House");
        NextMap = "Default";
    }
    if (NextMap == "Farm")
    {
        ChangeLevel("Farm");
        NextMap = "Default";
    }

}