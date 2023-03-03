#include <GameEnginePlatform/GameEngineWindow.h>

#include "ContentsCore.h"
#include "Level_Title.h"
#include "Level_Farm.h"
#include "Level_Road.h"
#include "Level_House.h"
#include "Level_Mine.h"
#include "globalValue.h"
#include "globalInterface.h"
#include "ContentsEnum.h"
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
	CreateLevel<Level_Road>("Road");
	CreateLevel<Level_House>("House");
	CreateLevel<Level_Mine>("Mine");

	ChangeLevel("Mine");

    CurLevel = "Mine";   
}

void ContentsCore::Update()
{

    if (isSet == 0)
    {
        globalInterface::CreateItemToAllInventory("PickIcon.bmp", static_cast<int>(ItemType::Pick));
        globalInterface::CreateItemToAllInventory("AxeIcon.bmp", static_cast<int>(ItemType::Axe));
        globalInterface::CreateItemToAllInventory("HoeIcon.bmp", static_cast<int>(ItemType::Hoe));
        globalInterface::CreateItemToAllInventory("WateringIcon.bmp", static_cast<int>(ItemType::Watering));
        
        SoundContoller.SoundInit();

        for (int i = 0; i < 2; i++)
        {
            globalInterface::CreateItemToAllInventory("SeedParsnip.bmp", static_cast<int>(ItemType::Seed));
            globalInterface::CreateItemToAllInventory("SeedGarlic.bmp", static_cast<int>(ItemType::Seed));
            globalInterface::CreateItemToAllInventory("SeedBean.bmp", static_cast<int>(ItemType::Seed));
        }

        isSet = 1;
    }

    SoundContoller.BGM_On(CurLevel);

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
        CurLevel = "House";
    }

    if (NextMap == "Farm")
    {
        ChangeLevel("Farm");
        CurLevel = "Farm";
    }

    if (NextMap == "Road")
    {
        ChangeLevel("Road");
        CurLevel = "Road";
    }

    if (NextMap == "Mine")
    {
        ChangeLevel("Mine");
        CurLevel = "Mine";
    }

    NextMap = "Default";
}