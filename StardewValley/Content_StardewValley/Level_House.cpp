#include "Level_House.h"
#include "House.h"
#include "Player.h"
#include "Inventory.h"
#include "UI.h"
#include "globalValue.h"
#include "Mouse.h"

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
    HousePlayer->ChangePlayerIdle();
}

void Level_House::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
    globalValue::SetcameraLimitPos(float4{ 1280, 768 } - GameEngineWindow::GetScreenSize());

    Player::SetMyPlayer(HousePlayer);
    Player::GetPlayer()->SetPos({ 475, 600 });
   

    SetCameraPos({0,0});

    if (_PrevLevel!=nullptr &&_PrevLevel->GetName() == "Farm")
    {
        Player::GetPlayer()->SetPos({ 490, 600 });
    }

    globalValue::SetCurLevelName(GetName());

    Inventory::ChangeGlobalInventory(HouseInventory);
    globalValue::AllInventoryItemOn();

    if (Player::GetIsCollision() == true)
    {
        Player::SetIsCollision(false);
    }
}

void Level_House::Loading()
{
    GameEngineDirectory Dir;

    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");

    {

        Dir.Move("Map");

        GameEngineImage* House = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("House.BMP"));
        GameEngineImage* HouseC = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HouseC.BMP"));

        Dir.MoveParent();
    }

    //»ç¿îµå
    {
       
    }
    CreateActor<House>();
    CreateActor<Mouse>();

    HousePlayer = CreateActor<Player>();   

    Player::GetPlayer()->SetPos({ 475, 600 });
    SetCameraPos({ 0,0 });
}

void Level_House::Update(float _DeltaTime)
{
}
