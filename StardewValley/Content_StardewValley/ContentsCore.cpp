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
}

void ContentsCore::Update()
{

    if (isSet == 0)
    {
        globalValue::CreateItemToAllInventory("PickIcon.bmp", static_cast<int>(ItemType::Pick));
        globalValue::CreateItemToAllInventory("AxeIcon.bmp", static_cast<int>(ItemType::Axe));
        globalValue::CreateItemToAllInventory("HoeIcon.bmp", static_cast<int>(ItemType::Hoe));
        globalValue::CreateItemToAllInventory("WateringIcon.bmp", static_cast<int>(ItemType::Watering));

        for (int i = 0; i < 1; i++)
        {
            globalValue::CreateItemToAllInventory("SeedParsnip.bmp", static_cast<int>(ItemType::Seed));
        }

        isSet = 1;
    }

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
    }

    if (NextMap == "Farm")
    {
        ChangeLevel("Farm");
    }

    if (NextMap == "Road")
    {
        ChangeLevel("Road");
    }

    NextMap = "Default";
}