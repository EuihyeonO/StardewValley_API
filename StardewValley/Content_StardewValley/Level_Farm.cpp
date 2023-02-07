#include <string>

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Level_Farm.h"
#include "Farm.h"
#include "Player.h"
#include "UI.h"
#include "Inventory.h"
#include "Item.h"
#include "ContentsEnum.h"
#include "Crops.h"

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

        GameEngineImage* Hoe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Hoe.BMP"));
        Hoe->Cut(6, 1);
        GameEngineImage* LHoe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LHoe.BMP"));
        LHoe->Cut(6, 1);
        GameEngineImage* DHoe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DHoe.BMP"));
        DHoe->Cut(5, 1);
        GameEngineImage* UHoe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UHoe.BMP"));
        UHoe->Cut(5, 1);
    }

    //액터생성
    CreateActor<Player>(ActorType::Player);
    CreateActor<Farm>();
    CreateActor<UI>();
    CreateActor<Inventory>();
}

void Level_Farm::Update(float _DeltaTime)
{

   


    //농사 테스트용 코드
    if (GameEngineInput::IsKey("MakeCrop") == false)
    {
        GameEngineInput::CreateKey("MakeCrop", 'O');
    }

    if (GameEngineInput::IsDown("MakeCrop"))
    {
        CropList.push_back(CreateActor<Crops>(ActorType::Crops));
        CropList[0]->InitCrop("Parsnip.bmp", Player::GetPlayer()->GetPos());        
    }


    
    //상호작용키 E를 눌렀을 떄, 만약 인벤토리에서 현재 선택된 아이템이
    //씨앗 종류임을 여기서 먼저 검사
    //결과 true라면 CrateActor<Crops>(Crop); 함수 호출
    //이후 actor범위에서 tool과 crop의 충돌을 검사 후 , true일 때마다 life를 1씩 감소
    //crop의 life가 0이 되면 여기서 createActor<Item>(Item);을 한뒤 inventory에 push.back


}