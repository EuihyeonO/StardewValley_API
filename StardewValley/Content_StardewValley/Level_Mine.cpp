#include "UI.h"
#include "Mine.h"
#include "Player.h"
#include "Mouse.h"
#include "Inventory.h"

#include "Level_Mine.h"

#include "globalValue.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatForm/GameEngineWindow.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineTileMap.h>


 Inventory* Level_Mine::MineInventory;
 UI* Level_Mine::MineUI;

Level_Mine::Level_Mine()
{
    MineInventory = CreateActor<Inventory>();
    MineUI = CreateActor<UI>();
}

Level_Mine::~Level_Mine()
{
}

void Level_Mine::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}
void Level_Mine::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
    //플레이어 위치설정
    Player::SetMyPlayer(MinePlayer);
    Player::ChangePlayerIdle("D");
    Player::GetPlayer()->ChangePlayerAnimation("DIdle");
    MinePlayer->PlayerStop();
    MinePlayer->SetPos({ 640, 100 });

    //카메라 위치설정
    globalValue::SetcameraLimitPos(float4{ 1280, 768 } - GameEngineWindow::GetScreenSize());
    SetCameraPos({ 0,0 });
    
    //인벤토리 설정
    Inventory::ChangeGlobalInventory(MineInventory);
    UI::SetglobalUI(MineUI);
    globalValue::AllInventoryItemOn();

    MineInventory->SetItemPos();
    
    MineController->PortalFarmOn();
    MineController->SetIsFading(2);

    //MineTileMap->GetTile(0, { 500, 500 })->CreateAnimation({ .AnimationName = "Break",.ImageName = "stoneDebris.bmp",.FrameIndex = {1,2,3,4} ,.FrameTime = {0.1f, 0.1f, 0.1f, 0.1f} });
    //MineTileMap->GetTile(0, { 500, 500 })->CreateAnimation({ .AnimationName = "Idle",.ImageName = "stoneDebris.bmp",.FrameIndex = {0} ,.FrameTime = {0.1f} });
    //MineTileMap->GetTile(0, { 500, 500 })->ChangeAnimation("Idle");
}

void Level_Mine::Loading()
{
    ImageRoad();

    MineController = CreateActor<Mine>();
    MinePlayer = CreateActor<Player>();
    CreateActor<Mouse>();

    GameEngineRandom::MainRandom.SetSeed(time(NULL));

    MineTileMap = CreateActor<GameEngineTileMap>();
    MineTileMap->CreateTileMap(1280 / 64, 768 / 64, 10, 30, { 64,64 });
    MineTileMap->SetFloorSetting(0, "stoneDebris.bmp");

    SetTileObject();
}
void Level_Mine::Update(float _DeltaTime)
{
    if (GameEngineInput::IsDown("Debug") == true)
    {
        MineTileMap->GetTile(0, { 500, 500 })->ChangeAnimation("Break");
    }

    if (MineTileMap->GetTile(0, { 500, 500 })->GetFrame() == 4)
    {
        MineTileMap->GetTile(0, { 500, 500 })->Off();
    }
}

void Level_Mine::ImageRoad()
{
    GameEngineDirectory Dir;

    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");

    {
        Dir.Move("Map");

        GameEngineImage* Mine = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Mine.BMP"));
        GameEngineImage* MineLayer = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MineLayer.BMP"));
        GameEngineImage* MineC = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MineC.BMP"));

        Dir.MoveParent();
    }

    {
        GameEngineImage* stone = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("stoneDebris.BMP"));
        stone->Cut(5, 1);
    }
}

void Level_Mine::SetTileObject()
{
    float X = GameEngineRandom::MainRandom.RandomInt(0, 19);
    float Y = GameEngineRandom::MainRandom.RandomInt(0, 11);

    X *= 64;
    Y *= 64;

    GameEngineImage* ColMine = GameEngineResources::GetInst().ImageFind("MineC.bmp");

    for (int i = 0; i < 10; i++)
    {
        //이미 그 인덱스의 타일이 세팅되어 있거나 마젠타컬러로 제한해둔 위치를 벗어났다면, 다시 추출한다.
        while (MineTileMap->GetTile(0, { X, Y })->IsUpdate() == true ||
            RGB(255, 0, 255) != ColMine->GetPixelColor(float4(X, Y), RGB(255, 0, 255)))
        {
            X = GameEngineRandom::MainRandom.RandomInt(0, 19);
            Y = GameEngineRandom::MainRandom.RandomInt(0, 11);

            X *= 64;
            Y *= 64;
        }

        MineTileMap->SetTileFrame(0, { X, Y }, 0);
        MineTileMap->GetTile(0, { X, Y })->CreateAnimation({ .AnimationName = "Break",.ImageName = "stoneDebris.bmp",.FrameIndex = {1,2,3,4} ,.FrameTime = {0.1f, 0.1f, 0.1f, 0.1f} });
        MineTileMap->GetTile(0, { X, Y })->CreateAnimation({ .AnimationName = "Idle",.ImageName = "stoneDebris.bmp",.FrameIndex = {0} ,.FrameTime = {0.1f} });
        MineTileMap->GetTile(0, { X, Y })->ChangeAnimation("Idle");
    }
}