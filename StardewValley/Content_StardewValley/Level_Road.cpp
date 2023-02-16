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
#include "Crops.h"
#include "globalValue.h"

Inventory* Level_Road::RoadInventory;

Level_Road::Level_Road()
{
    RoadInventory = CreateActor<Inventory>();
}

Level_Road::~Level_Road()
{
}

void Level_Road::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void Level_Road::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
    globalValue::SetcameraLimitPos(float4{ 1920, 1646 } - GameEngineWindow::GetScreenSize());
    Player::SetMyPlayer(RoadPlayer);
    RoadPlayer->SetPos({ 80, 1280 });

    Inventory::CopyItemList(RoadInventory);
    globalValue::SetCurLevelName(GetName());
}

void Level_Road::Loading()
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
        GameEngineImage* Pierre = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Pierre.BMP"));
        Dir.MoveParent();
    }

    CreateActor<Road>();
    RoadPlayer = CreateActor<Player>();
    RoadPlayer->SetPos({ 100, 1280 });  
    CreateActor<UI>();
}

void Level_Road::Update(float _DeltaTime)
{
}
