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
Level_Farm* Level_Farm::FarmManager = nullptr;

Level_Farm::Level_Farm()
{  
    FarmManager = this;
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
    Player::SetMyPlayer(FarmPlayer);
    Inventory::CopyItemList(FarmInventory);
    Player::ChangePlayerIdle();
}

void Level_Farm::Loading()
{
    GameEngineDirectory Dir;

    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");

    //���� ��
    {
        GameEngineImage* Farm = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Farm.BMP"));
        GameEngineImage* FarmLayer = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FarmLayer.BMP"));
        GameEngineImage* FarmC = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FarmC.BMP"));
    }
    //�������̽�
    {
        GameEngineImage* Quickslot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Quickslot.BMP"));
        GameEngineImage* TimeBar = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TimeBar.BMP"));
        GameEngineImage* StatusBar = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("StatusBar.BMP"));

        GameEngineImage* Inventory = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Inventory.BMP"));       
    }
    //�÷��̾�
    {
        GameEngineImage* Player = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Player.BMP"));
        Player->Cut(6, 21);

        GameEngineImage* Playerleft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Playerleft.BMP"));
        Playerleft->Cut(6, 21);
    }
    //���۹�
    {
        Dir.Move("Crops");
        
        GameEngineImage* Parsnip = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Parsnip.BMP"));
        Parsnip->Cut(6, 1);
        GameEngineImage* ParsnipT = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ParsnipT.BMP"));
    }
    //����
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
        DWatering->Cut(5, 1); 
        GameEngineImage* RWatering = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Watering.BMP"));
        RWatering->Cut(5, 1); 
        GameEngineImage* LWatering = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LWatering.BMP"));
        LWatering->Cut(5, 1);
        GameEngineImage* UWatering = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UWatering.BMP"));
        UWatering->Cut(3, 1);

        GameEngineImage* WateringIcon = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WateringIcon.BMP"));
    }

    //���ͻ���  
    CreateActor<Farm>();
    CreateActor<UI>();

    FarmPlayer = CreateActor<Player>(ActorType::Player);
    FarmInventory = CreateActor<Inventory>();


    Player::GetPlayer()->SetPos({ 1350, 600 });
    SetCameraPos({ Player::GetPlayer()->GetPos().x - 640, Player::GetPlayer()->GetPos().y - 384 });
}

void Level_Farm::Update(float _DeltaTime)
{  
}

void Level_Farm::CreateCrops(std::string _CropName)
{
    //Crop Ŭ������ static ���� CropList�� ��������� ���� ��, Actor �ܰ迡�� �����ϵ��� ����
    if (GameEngineInput::IsDown("MakeCrop"))
    {
        CropList.push_back(CreateActor<Crops>());
        CropList[CropList.size() - 1]->SetName(_CropName);
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
