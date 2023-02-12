#include "Level_House.h"
#include "House.h"
#include "Player.h"
#include "Inventory.h"
#include "globalValue.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>

Inventory* Level_House::HouseInventory = nullptr;

Level_House::Level_House()
{
}

Level_House::~Level_House()
{
}

void Level_House::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void Level_House::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
    globalValue::SetcameraLimitPos(float4{ 1280, 768 } - GameEngineWindow::GetScreenSize());

    Player::SetMyPlayer(HousePlayer);
    Player::GetPlayer()->SetPos({ 475, 600 });

    Inventory::CopyItemList(HouseInventory);
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
        GameEngineImage* House = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("House.BMP"));
        GameEngineImage* HouseC = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HouseC.BMP"));
    }

    CreateActor<House>();

    HousePlayer = CreateActor<Player>();
    HouseInventory = CreateActor<Inventory>();

    Player::GetPlayer()->SetPos({ 475, 600 });
    SetCameraPos({ 0,0 });
}

void Level_House::Update(float _DeltaTime)
{
}