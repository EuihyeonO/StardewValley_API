#include <string>
#include <vector>

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTileMap.h>

#include "Level_Farm.h"
#include "Farm.h"
#include "Player.h"
#include "UI.h"
#include "Inventory.h"
#include "Item.h"
#include "ContentsEnum.h"
#include "Crops.h"
#include "Mouse.h"
#include "globalValue.h"
#include "SelectedLine.h"


std::vector<Crops*> Level_Farm::CropList;
GameEngineTileMap* Level_Farm::TileMap;
Inventory* Level_Farm::FarmInventory;
UI* Level_Farm::FarmUI;

Level_Farm::Level_Farm()
{  
    FarmInventory = CreateActor<Inventory>();
    FarmUI = CreateActor<UI>();
}

Level_Farm::~Level_Farm()
{
}

void Level_Farm::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
    FarmPlayer->ChangePlayerIdle();
}

void Level_Farm::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
    globalValue::SetcameraLimitPos(float4{ 2560 , 1024 } - GameEngineWindow::GetScreenSize());

    Player::SetMyPlayer(FarmPlayer);
    globalValue::AllInventoryItemOn();
    Player::ChangePlayerIdle();
    Inventory::ChangeGlobalInventory(FarmInventory);

    float4 PlayerPos = Player::GetPlayer()->GetPos();
    float4 HalfSize = GameEngineWindow::GetScreenSize().half();
    float4 CameraPos = PlayerPos - HalfSize;

    if (CameraPos.x <0)
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
    
    globalValue::SetCurLevelName(GetName());

    if (_PrevLevel!=nullptr && _PrevLevel->GetName() == "Road")
    {
        FarmPlayer->SetPos({ 2490, 512 });
    }
    else if (_PrevLevel != nullptr  && _PrevLevel->GetName() == "House")
    {
        FarmPlayer->SetPos({ 1645, 442 });
        SetCameraPos({ FarmPlayer->GetPos().x - 640, FarmPlayer->GetPos().y - 384});
    }

}

void Level_Farm::Loading()
{
    GameEngineDirectory Dir;

    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");

    //
    {
        GameEngineImage* HoeDirt = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HoeDirt.BMP"));
        HoeDirt->Cut(2, 1);
    }
    //농장 맵
    {
        Dir.Move("Map");

        GameEngineImage* Farm = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Farm.BMP"));
        GameEngineImage* FarmLayer = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FarmLayer.BMP"));
        GameEngineImage* FarmC = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FarmC.BMP"));

        Dir.MoveParent();
    }
    //인터페이스

    //플레이어
    {
        GameEngineImage* Player = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Player.BMP"));
        Player->Cut(6, 21);

        GameEngineImage* Playerleft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Playerleft.BMP"));
        Playerleft->Cut(6, 21);
    }
    //농작물
    {
        Dir.Move("Crops");
        
        GameEngineImage* Parsnip = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Parsnip.BMP"));
        Parsnip->Cut(6, 1);
        GameEngineImage* IconParsnip = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IconParsnip.BMP"));
        GameEngineImage* SeedParsnip = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SeedParsnip.BMP"));
       
        GameEngineImage* Cauliflower = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Cauliflower.BMP"));
        Cauliflower->Cut(7, 1);     
        GameEngineImage* IconCauliflower = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IconCauliflower.BMP"));
        GameEngineImage* SeedCauliflower = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SeedCauliflower.BMP"));

        GameEngineImage* Garlic = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Garlic.BMP"));
        Garlic->Cut(5, 1);
        GameEngineImage* IconGarlic = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IconGarlic.BMP"));
        GameEngineImage* SeedGarlic = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SeedGarlic.BMP"));

        GameEngineImage* Bean = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Bean.BMP"));
        Bean->Cut(8, 1);
        GameEngineImage* IconBean = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IconBean.BMP"));
        GameEngineImage* SeedBean = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SeedBean.BMP"));

        Dir.MoveParent();
    }
    //도구
    {
       
        Dir.Move("Tools");      

        GameEngineImage* Pick = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Pick.BMP"));
        Pick->Cut(6, 1);
        GameEngineImage* LPick = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LPick.BMP"));
        LPick->Cut(6, 1);
        GameEngineImage* DPick = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DPick.BMP"));
        DPick->Cut(5, 1);
        GameEngineImage* UPick = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UPick.BMP"));
        UPick->Cut(5, 1);

        GameEngineImage* PickIcon = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PickIcon.BMP"));


        GameEngineImage* Axe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Axe.BMP"));
        Axe->Cut(6, 1);
        GameEngineImage* LAxe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LAxe.BMP"));
        LAxe->Cut(6, 1);
        GameEngineImage* DAxe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DAxe.BMP"));
        DAxe->Cut(5, 1);
        GameEngineImage* UAxe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UAxe.BMP"));
        UAxe->Cut(5, 1);

        GameEngineImage* AxeIcon = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AxeIcon.BMP"));

        GameEngineImage* Hoe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Hoe.BMP"));
        Hoe->Cut(6, 1);
        GameEngineImage* LHoe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LHoe.BMP"));
        LHoe->Cut(6, 1);
        GameEngineImage* DHoe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DHoe.BMP"));
        DHoe->Cut(5, 1);
        GameEngineImage* UHoe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UHoe.BMP"));
        UHoe->Cut(5, 1);

        GameEngineImage* HoeIcon = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HoeIcon.BMP"));

        GameEngineImage* DWatering = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DWatering.BMP"));
        DWatering->Cut(5, 1); 
        GameEngineImage* RWatering = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Watering.BMP"));
        RWatering->Cut(5, 1); 
        GameEngineImage* LWatering = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LWatering.BMP"));
        LWatering->Cut(5, 1);
        GameEngineImage* UWatering = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UWatering.BMP"));
        UWatering->Cut(3, 1);

        GameEngineImage* WateringIcon = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WateringIcon.BMP"));

        GameEngineImage* Default = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Default.BMP"));

        Dir.MoveParent();
    }

    {       
    }

    //액터생성  
    TileMap = CreateActor<GameEngineTileMap>();
    FarmPlayer = CreateActor<Player>();

    CreateActor<Farm>();
    CreateActor<Mouse>();
    CreateActor<SelectedLine>();

    //FarmInventory = CreateActor<Inventory>();

    Player::GetPlayer()->SetPos({ 1350, 600 });
    SetCameraPos({ Player::GetPlayer()->GetPos().x - 640, Player::GetPlayer()->GetPos().y - 384 });

    InitTile();
}

void Level_Farm::Update(float _DeltaTime)
{  
}

void Level_Farm::CreateCrops(std::string _CropName)
{
    if (GameEngineInput::IsDown("MakeCrop"))
    {            
        float4 Pos = FarmPlayer->GetInteractPos();
        int Zindex = CheckUpdateTile(Pos);

        if (TileMap->GetTile(0, Pos)->GetFrame() == 1 && Zindex != -1)
        {
            TileMap->SetTileFrame(0, Pos, 0);

            int frame = TileMap->GetTile(Zindex, Pos)->GetFrame();

            if (frame >= GetLastIndexCrops(Zindex))
            {
                return;
            }
            TileMap->SetTileFrame(Zindex, Pos, frame + 1);
        }
    }
}

void Level_Farm::DeathCrops(Crops* _Crop)
{
    for (int i = 0; i < CropList.size(); i++)
    {
        if (CropList[i] == _Crop)
        {
            CropList.erase(CropList.begin() + i);
            return;
        }
    }
}

