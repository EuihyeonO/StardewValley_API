#include "UI.h"
#include "Mine.h"
#include "Player.h"
#include "Mouse.h"
#include "Inventory.h"
#include "Level_Mine.h"
#include "ContentsEnum.h"
#include "globalValue.h"
#include "globalInterface.h"
#include "MenuButton.h"
#include "AffectionBox.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatForm/GameEngineWindow.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineTileMap.h>

#include <vector>
#include <string_view>


 Inventory* Level_Mine::MineInventory;
 GameEngineTileMap* Level_Mine::MineTileMap;
 std::vector<GameEngineCollision*> Level_Mine::OnCollisionList;
 std::vector<std::vector<int>> Level_Mine::StoneLife(12, std::vector<int>(20, -1));
 UI* Level_Mine::MineUI;
 int Level_Mine::isFirst = 0;

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
    globalInterface::AllInventoryItemOn();
    MenuButton::SetGlobalMenuButton(MineMenuButton);
    AffectionBox::SetGlobalAffectionBox(MineAffectionBox);

    MineInventory->SetItemPos();
    
    MineController->PortalFarmOn();
    MineController->SetIsFading(2);
}

void Level_Mine::Loading()
{
    ImageRoad();

    MineController = CreateActor<Mine>();
    MinePlayer = CreateActor<Player>();
    MineMenuButton = CreateActor<MenuButton>();
    MineAffectionBox = CreateActor<AffectionBox>();
    CreateActor<Mouse>();

    GameEngineRandom::MainRandom.SetSeed(time(NULL));

    MineTileMap = CreateActor<GameEngineTileMap>();
    MineTileMap->CreateTileMap(1280 / 64, 768 / 64, 10, 30, { 64,64 });

    MineTileMap->CreateTileMapCollision(1280 / 64, 768 / 64, 1, static_cast<int>(ActorType::Stone), { 64,64 });

    MineTileMap->SetFloorSetting(static_cast<int>(MineralName::Stone), "Stone.bmp");
    MineTileMap->SetFloorSetting(static_cast<int>(MineralName::Topaz), "Topaz.bmp");

    CreateTileAnimation(static_cast<int>(MineralName::Stone), "Stone.bmp");
    CreateTileAnimation(static_cast<int>(MineralName::Topaz), "Topaz.bmp");

    SetTileObject();
}
void Level_Mine::Update(float _DeltaTime)
{
    //if (GameEngineInput::IsDown("Debug") == true)
    //{
    //    MineTileMap->GetTile(0, { 500, 500 })->ChangeAnimation("Break");
    //}

    //if (MineTileMap->GetTile(0, { 500, 500 })->GetFrame() == 4)
    //{
    //    MineTileMap->GetTile(0, { 500, 500 })->Off();
    //}

    TileUpdate();
    isToolCollisionToTile();
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
        GameEngineImage* stone = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Stone.BMP"));
        GameEngineImage* stoneIcon = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Iconstone.BMP"));
        GameEngineImage* VibStone = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("VibStone.BMP"));
        
        GameEngineImage* Topaz = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Topaz.BMP"));
        GameEngineImage* TopazIcon = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IconTopaz.BMP"));
        GameEngineImage* VibTopaz = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("VibTopaz.BMP"));
        VibStone->Cut(3, 1);
        VibTopaz->Cut(3, 1);
        stone->Cut(7, 1);
        Topaz->Cut(7, 1);
    }
}

void Level_Mine::SetTileObject()
{
    SetMineralToTile(static_cast<int>(MineralName::Stone), "Stone.bmp");
    SetMineralToTile(static_cast<int>(MineralName::Topaz), "Topaz.bmp");
}

bool Level_Mine::isCollisionToTile(float4 _pos)
{

    for (int i = 0; i < OnCollisionList.size(); i++)
    {
        if (true == OnCollisionList[i]->Collision({.TargetGroup = static_cast<int>(ActorType::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect}))
        {
            return true;
        }
    }

    return false;
}

bool Level_Mine::isToolCollisionToTile()
{

    for (int i = 0; i < OnCollisionList.size(); i++)
    {
        if (true == OnCollisionList[i]->Collision({ .TargetGroup = static_cast<int>(ActorType::Tool), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
        {
           return true;
        }
    }

    return false;
}

int Level_Mine::CheckUpdateTile(float4 _pos)
{
    for (int i = 0; i < 2; i++)
    {
        if (MineTileMap->GetTile(i, _pos)->IsUpdate() == true)
        {
            return i;
        }
    }
    return -1;
}

void Level_Mine::SubToStoneLife(float4 _pos)
{
    int X = _pos.x / 64;
    int Y = _pos.y / 64;
   
    --StoneLife[Y][X];
}

void Level_Mine::BreakStone(int _floor, float4 _pos)
{
    int X = _pos.x / 64;
    int Y = _pos.y / 64;


    if (StoneLife[Y][X] == 0)
    {
        MineTileMap->GetTile(_floor, _pos)->ChangeAnimation("Break");
        GetMineral(_floor);
    } 
}

void Level_Mine::TileUpdate()
{
    int X, Y;
    int Floor;

    for (int i = 0; i<StoneLife.size(); i++)
    {
        for (int j = 0; j<StoneLife[i].size(); j++)
        {

            X = j * 64;
            Y = i * 64;
            Floor = CheckUpdateTile(float4(X, Y));

            if (StoneLife[i][j] == 0 && Floor != -1)
            {
                BreakStone(Floor, float4(X, Y));
                StoneLife[i][j] = -1;               
            }

            if (Floor != -1 && MineTileMap->GetTileFrame(Floor, float4(X, Y)) != 0 && MineTileMap->GetTile(Floor, float4(X, Y))->IsAnimationEnd() == true)
            {
                MineTileMap->GetTile(Floor, float4(X, Y))->Off();
                MineTileMap->GetTileCollision(0, float4(X, Y))->Off();
                StoneLife[i][j] = -1;
                for (int i = 0; i < OnCollisionList.size(); i++)
                {
                    if (OnCollisionList[i] == MineTileMap->GetTileCollision(0, float4(X, Y)))
                    {
                        OnCollisionList.erase(OnCollisionList.begin()+i);
                        break;
                    }
                }
            }
        }
    }
}

void Level_Mine::SetMineralToTile(int _Num, const std::string_view& _ImageName)
{
    int X = GameEngineRandom::MainRandom.RandomInt(0, 19);
    int Y = GameEngineRandom::MainRandom.RandomInt(3, 11);

    X *= 64;
    Y *= 64;

    GameEngineRender* Tile;
    GameEngineCollision* TileCollision;
    GameEngineImage* ColMine = GameEngineResources::GetInst().ImageFind("MineC.bmp");

    for (int i = 0; i < 5; i++)
    {
        //이미 그 인덱스의 타일이 세팅되어 있거나 마젠타컬러로 제한해둔 위치를 벗어났다면, 다시 추출한다.
        while (
            StoneLife[Y / 64][X/ 64] != -1 ||
            CheckUpdateTile(float4(X, Y)) != -1 ||
            RGB(255, 0, 255) != ColMine->GetPixelColor(float4(X, Y), RGB(255, 0, 255)))
        {
            X = GameEngineRandom::MainRandom.RandomInt(0, 19);
            Y = GameEngineRandom::MainRandom.RandomInt(3, 11);

            X *= 64;
            Y *= 64;
        }

        MineTileMap->SetTileFrame(_Num, float4(X, Y), 0);

        Tile = MineTileMap->GetTile(_Num, float4(X, Y));

        TileCollision = MineTileMap->GetTileCollision(0, float4(X, Y));
        TileCollision->On();
        TileCollision->SetDebugRenderType(CT_Rect);
        OnCollisionList.push_back(TileCollision);

        StoneLife[Y / 64][X / 64] = 5;

    }
}


void Level_Mine::DeleteTile()
{
    OnCollisionList.clear();

    for (int Y = 0; Y < 12; Y++)
    {
        for (int X = 0; X < 20; X++)
        {
            StoneLife[Y][X] = -1;

            int floor = CheckUpdateTile(float4(X * 64, Y * 64));

             if (floor != -1)
            {
                MineTileMap->GetTile(floor, float4(X * 64, Y * 64))->Off();
            }
        }
    }
}

void Level_Mine::CreateTileAnimation(int _MinaralName, const std::string_view& _ImageName)
{
    int X, Y;
    std::string Name = _ImageName.data();
    std::string PlusName = "Vib" + Name;

    for (Y = 0; Y < 12; Y++)
    {
        for (X = 0; X < 20; X++)
        {
            GameEngineRender* Tile = MineTileMap->GetTile(_MinaralName, float4(X * 64, Y * 64));
            
            Tile->CreateAnimation({ .AnimationName = "Break",.ImageName = _ImageName,.FrameIndex = {1,2,3,4,5,6} ,.FrameTime = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f} });
            Tile->CreateAnimation({ .AnimationName = "Vib",.ImageName = PlusName,.FrameIndex = {0,1,2} ,.FrameTime = {0.1f, 0.1f, 0.1f}});
            Tile->CreateAnimation({ .AnimationName = "Idle",.ImageName = _ImageName,.FrameIndex = {0} ,.FrameTime = {0.1f} });
            Tile->ChangeAnimation("Idle");
        }
    }
}

void Level_Mine::GetMineral(int _MineralName)
{
    //globalInterface::CreateItemToAllInventory_Mineral(_MineralName);
}