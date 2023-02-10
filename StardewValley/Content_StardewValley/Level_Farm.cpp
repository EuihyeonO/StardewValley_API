#include <string>

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "Level_Farm.h"
#include "Farm.h"
#include "Player.h"
#include "UI.h"
#include "Inventory.h"
#include "Item.h"
#include "ContentsEnum.h"
#include "Crops.h"
#include "globalValue.h"

std::vector<Crops*> Level_Farm::CropList;

Level_Farm::Level_Farm()
{
}

Level_Farm::~Level_Farm()
{
}

void Level_Farm::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void Level_Farm::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
    globalValue::SetcameraLimitPos(float4{ 2560 , 1024 } - GameEngineWindow::GetScreenSize());
}

void Level_Farm::Loading()
{
    GameEngineDirectory Dir;

    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");

    //농장 맵
    {
        GameEngineImage* Farm = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Farm.BMP"));
        GameEngineImage* FarmLayer = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FarmLayer.BMP"));
        GameEngineImage* FarmC = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FarmC.BMP"));
    }
    //인터페이스
    {
        GameEngineImage* Quickslot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Quickslot.BMP"));
        GameEngineImage* House = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("House.BMP"));
        GameEngineImage* TimeBar = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TimeBar.BMP"));
        GameEngineImage* StatusBar = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("StatusBar.BMP"));

        GameEngineImage* Inventory = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Inventory.BMP"));       
    }
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
    }
    //도구
    {
        Dir.MoveParent();
        Dir.Move("Tools");

        GameEngineImage* SelectedLine = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectedLine.BMP"));

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
        DWatering->Cut(3, 1); 
        GameEngineImage* RWatering = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Watering.BMP"));
        RWatering->Cut(5, 1); 
        GameEngineImage* LWatering = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LWatering.BMP"));
        LWatering->Cut(3, 1);
        GameEngineImage* UWatering = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UWatering.BMP"));
        UWatering->Cut(3, 1);

        GameEngineImage* WateringIcon = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WateringIcon.BMP"));
    }

    //액터생성
    CreateActor<Player>(ActorType::Player);
    CreateActor<Farm>();
    CreateActor<UI>();
    CreateActor<Inventory>();

}

void Level_Farm::Update(float _DeltaTime)
{  
}

void Level_Farm::CreateCrops(std::string _CropName)
{
    //Crop 클래스에 static 으로 CropList를 멤버변수로 선언 후, Actor 단계에서 관리하도록 하자
    if (GameEngineInput::IsDown("MakeCrop"))
    {
        CropList.push_back(CreateActor<Crops>());
        CropList[CropList.size() - 1]->SetName(_CropName);
    }
}