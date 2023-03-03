#include <string>

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTileMap.h>

#include "Level_Farm.h"
#include "Level_Road.h"
#include "Farm.h"
#include "Player.h"
#include "UI.h"
#include "Inventory.h"
#include "Item.h"
#include "Road.h"
#include "ContentsEnum.h"
#include "globalValue.h"
#include "Pierre.h"
#include "Mouse.h"
#include "MenuButton.h"
#include "AffectionBox.h"
#include "Lewis.h"
#include "Sam.h"
#include "Penny.h"
#include "Haley.h"

Inventory* Level_Road::RoadInventory;
UI* Level_Road::RoadUI;
Pierre* Level_Road::NPCPierre;

Level_Road::Level_Road()
{
    RoadInventory = CreateActor<Inventory>();
    RoadUI = CreateActor<UI>();
}

Level_Road::~Level_Road()
{
}

void Level_Road::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
    RoadPlayer->ChangePlayerIdle("L");
}

void Level_Road::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
    globalValue::SetCurLevelName(GetName());


    //플레이어 설정
    Player::SetMyPlayer(RoadPlayer);
    RoadPlayer->SetPos({ 80, 1280 });

    //카메라 기초설정
    globalValue::SetcameraLimitPos(float4{ 1920, 1646 } - GameEngineWindow::GetScreenSize());

    float4 PlayerPos = Player::GetPlayer()->GetPos();
    float4 HalfSize = GameEngineWindow::GetScreenSize().half();
    float4 CameraPos = PlayerPos - HalfSize;

    if (CameraPos.x < 0)
    {
        CameraPos.x = 0;
    }
    else if (globalValue::GetcameraLimitPos().x < CameraPos.x)
    {
        CameraPos.x = globalValue::GetcameraLimitPos().x;
    }

    if (CameraPos.y < 0)
    {
        CameraPos.y = 0;
    }
    else if (globalValue::GetcameraLimitPos().y < CameraPos.y)
    {
        CameraPos.y = globalValue::GetcameraLimitPos().y;
    }

    SetCameraPos(CameraPos);

    //인벤토리 설정
    Inventory::ChangeGlobalInventory(RoadInventory);
    UI::SetglobalUI(RoadUI);
    MenuButton::SetGlobalMenuButton(RoadMenuButton);
    AffectionBox::SetGlobalAffectionBox(RoadAffectionBox);
    RoadInventory->SetItemPos();

    //엔피씨 설정
    NPCPierre->ShopOff();
}

void Level_Road::Loading()
{
    ImageRoad();

    CreateActor<Road>();
    CreateActor<Mouse>();

    RoadPlayer = CreateActor<Player>();   
    NPCPierre = CreateActor<Pierre>();
    CreateActor<Haley>();
    CreateActor<Lewis>();
    CreateActor<Sam>();
    CreateActor<Penny>();

    RoadMenuButton = CreateActor<MenuButton>();
    RoadAffectionBox = CreateActor<AffectionBox>();

}

void Level_Road::Update(float _DeltaTime)
{
}

void Level_Road::ImageRoad()
{

    GameEngineDirectory Dir;

    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");
    //
    {
        Dir.Move("Map");
        GameEngineImage* Road = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Road.BMP"));
        GameEngineImage* RoadC = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoadC.BMP"));
        GameEngineImage* RoadLayer = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoadLayer.BMP"));
        Dir.MoveParent();
    }

    {
        Dir.Move("NPC");
        GameEngineImage* PierreRender = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Pierre.BMP"));
        GameEngineImage* HaleyRender = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Haley.BMP"));
        GameEngineImage* SamRender = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Sam.BMP"));
        GameEngineImage* PennyRender = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Penny.BMP"));
        GameEngineImage* LewisRender = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Lewis.BMP"));
        Dir.MoveParent();
    }

    {
        Dir.Move("UI");
        GameEngineImage* Shop = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Shop.BMP"));
        Dir.MoveParent();
    }

    {
        GameEngineImage* parsnipitem = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ItemParsnip.BMP"));
        GameEngineImage* hparsnipitem = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HoverItemParsnip.BMP"));

        GameEngineImage* Cauliflower = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ItemCauliflower.BMP"));
        GameEngineImage* hCauliflower = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HoverItemCauliflower.BMP"));

        GameEngineImage* Garlic = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ItemGarlic.BMP"));
        GameEngineImage* hGarlic = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HoverItemGarlic.BMP"));

        GameEngineImage* Bean = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ItemBean.BMP"));
        GameEngineImage* hBean = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HoverItemBean.BMP"));

    }
}