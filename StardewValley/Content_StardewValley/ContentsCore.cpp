#include <GameEnginePlatform/GameEngineWindow.h>

#include "ContentsCore.h"
#include "Level_Title.h"
#include "Level_Farm.h"
#include "globalValue.h"



ContentsCore ContentsCore::Core;

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
    GameEngineWindow::SettingWindowSize({1280, 720}); 
    GameEngineWindow::SettingWindowPos({277, 156}); 

    CreateLevel<Level_Title>("Title");
	CreateLevel<Level_Farm>("Farm");
	
	ChangeLevel("Title");
}

void ContentsCore::Update()
{
}

void ContentsCore::End()
{

}