#include "Level_House.h"
#include "House.h"
#include "Player.h"
#include "Inventory.h"
#include "UI.h"
#include "globalValue.h"
#include "globalInterface.h"
#include "Mouse.h"
#include "MenuButton.h"
#include "AffectionBox.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineFile.h>

Inventory* Level_House::HouseInventory = nullptr;
UI* Level_House::HouseUI = nullptr;

Level_House::Level_House()
{
    HouseInventory = CreateActor<Inventory>();
    HouseUI = CreateActor<UI>();
}

Level_House::~Level_House()
{
}

void Level_House::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
    HousePlayer->ChangePlayerIdle("D");
}

void Level_House::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

    globalValue::SetCurLevelName(GetName());

    //플레이어 설정
    Player::SetMyPlayer(HousePlayer);
    Player::GetPlayer()->SetPos({ 475, 600 });

    if (_PrevLevel != nullptr && _PrevLevel->GetName() == "Farm")
    {
        Player::GetPlayer()->SetPos({ 490, 600 });
        Player::GetPlayer()->PlayerStop();
        HouseController->SetIsFading(2);
        HouseController->PortalFarmOn();
    }

    if (Player::GetIsCollision() == true)
    {
        Player::SetIsCollision(false);
    }

    //카메라 위치설정
    globalValue::SetcameraLimitPos(float4{ 1280, 768 } - GameEngineWindow::GetScreenSize());
    SetCameraPos({0,0});
   
    //인벤토리 설정
    Inventory::ChangeGlobalInventory(HouseInventory);
    UI::SetglobalUI(HouseUI);
    globalInterface::AllInventoryItemOn();
    MenuButton::SetGlobalMenuButton(HouseMenuButton);
    AffectionBox::SetGlobalAffectionBox(HouseAffectionBox);
 
    HouseInventory->SetItemPos();

}

void Level_House::Loading()
{
    ImageRoad();

    CreateActor<Mouse>();
    HouseController = CreateActor<House>();
    HousePlayer = CreateActor<Player>();   
    HouseAffectionBox = CreateActor<AffectionBox>();
    HouseMenuButton = CreateActor<MenuButton>();

    Player::GetPlayer()->SetPos({ 475, 600 });
    SetCameraPos({ 0,0 });
}

void Level_House::Update(float _DeltaTime)
{

}

void Level_House::ImageRoad()
{
    GameEngineDirectory Dir;

    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");

    {

        Dir.Move("Map");

        GameEngineImage* House = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("House.BMP"));
        GameEngineImage* HouseLayer = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HouseLayer.BMP"));
        GameEngineImage* HouseC = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HouseC.BMP"));

        Dir.MoveParent();
    }
}