#include <GameEnginePlatform/GameEngineWindow.h>

#include "ContentsCore.h"
#include "Level_Title.h"
#include "Level_Farm.h"
#include "Level_Road.h"
#include "Level_House.h"
#include "globalValue.h"
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

	ChangeLevel("Road");

    CurLevel = "Road";
   
}

void ContentsCore::Update()
{

    if (isSet == 0)
    {
        globalValue::CreateItemToAllInventory("PickIcon.bmp", static_cast<int>(ItemType::Pick));
        globalValue::CreateItemToAllInventory("AxeIcon.bmp", static_cast<int>(ItemType::Axe));
        globalValue::CreateItemToAllInventory("HoeIcon.bmp", static_cast<int>(ItemType::Hoe));
        globalValue::CreateItemToAllInventory("WateringIcon.bmp", static_cast<int>(ItemType::Watering));

        SoundContoller.SoundInit();

        for (int i = 0; i < 2; i++)
        {
            globalValue::CreateItemToAllInventory("SeedParsnip.bmp", static_cast<int>(ItemType::Seed));
            globalValue::CreateItemToAllInventory("SeedGarlic.bmp", static_cast<int>(ItemType::Seed));
            globalValue::CreateItemToAllInventory("SeedBean.bmp", static_cast<int>(ItemType::Seed));
        }

        isSet = 1;
    }

    SoundContoller.SoundUpdate(CurLevel);
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

    NextMap = "Default";
}