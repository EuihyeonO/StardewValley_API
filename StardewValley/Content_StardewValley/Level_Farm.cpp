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
#include "SellBox.h"
#include "Player.h"
#include "UI.h"
#include "Inventory.h"
#include "Item.h"
#include "ContentsEnum.h"
#include "Mouse.h"
#include "globalValue.h"
#include "globalInterface.h"
#include "SelectedLine.h"
#include "AffectionBox.h"
#include "MenuButton.h"
#include "Marlon.h"
#include "Tree.h"
#include "Obstacle.h"


GameEngineTileMap* Level_Farm::TileMap;
Inventory* Level_Farm::FarmInventory;
UI* Level_Farm::FarmUI;
std::vector<GameEngineRender*> Level_Farm::OnTileList;

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
    FarmPlayer->ChangePlayerIdle("U");
}

void Level_Farm::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

    globalValue::SetCurLevelName(GetName());

    //플레이어 설정  
    Player::SetMyPlayer(FarmPlayer);

    if (_PrevLevel != nullptr && _PrevLevel->GetName() == "Road")
    {
        Player::ChangePlayerIdle("L");
        FarmPlayer->SetPos({ 2490, 512 });
    }
    else if (_PrevLevel != nullptr && _PrevLevel->GetName() == "House")
    {
        Player::ChangePlayerIdle("D");
        FarmPlayer->SetPos({ 1645, 442 });
        SetCameraPos({ FarmPlayer->GetPos().x - 640, FarmPlayer->GetPos().y - 384 });
        FarmPlayer->PlayerStop();
        FarmController->SetIsFading(2);
    }
    else if (_PrevLevel != nullptr && _PrevLevel->GetName() == "Mine")
    {
        FarmPlayer->SetPos({ 740, 352 });
        FarmPlayer->PlayerStop();
        FarmController->SetIsFading(2);
    }

    //카메라 기초설정
    globalValue::SetcameraLimitPos(float4{ 2560 , 1024 } - GameEngineWindow::GetScreenSize());

    float4 PlayerPos = Player::GetPlayer()->GetPos();
    float4 HalfSize = GameEngineWindow::GetScreenSize().half();
    float4 CameraPos = PlayerPos - HalfSize;

    if (CameraPos.x < 0)
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
  
    //인터페이스 설정
    Inventory::ChangeGlobalInventory(FarmInventory);
    UI::SetglobalUI(FarmUI);
    globalInterface::AllInventoryItemOn();
    MenuButton::SetGlobalMenuButton(FarmMenuButton);
    AffectionBox::SetGlobalAffectionBox(FarmAffectionBox);

    FarmInventory->SetItemPos();

    //포탈설정
    FarmController->PortalMineOn();   
}

void Level_Farm::Loading()
{

    ImageRoad();

    //액터생성  
    TileMap = CreateActor<GameEngineTileMap>();
    FarmPlayer = CreateActor<Player>();

    FarmController = CreateActor<Farm>();
    CreateActor<Mouse>();
    CreateActor<SelectedLine>();
    CreateActor<Obstacle>();
    CreateActor<SellBox>();

    FarmAffectionBox = CreateActor <AffectionBox>();
    FarmMenuButton = CreateActor <MenuButton>();

    CreateActor<Marlon>();

    for (int i = 0; i < 2; i++)
    {
        TreeList.push_back(CreateActor<Tree>());
    }
    TreeList[0]->SetPos({ 832, 768 });
    TreeList[1]->SetPos({ 1088, 832 });

    Player::GetPlayer()->SetPos({ 1350, 600 });
    SetCameraPos({ Player::GetPlayer()->GetPos().x - 640, Player::GetPlayer()->GetPos().y - 384 });

    InitTile();
}

void Level_Farm::Update(float _DeltaTime)
{  
    isCollisionToPlayer();

    myDeltaTime = _DeltaTime;
}

void Level_Farm::CreateCrops(std::string _CropName)
{
    if (GameEngineInput::IsDown("MakeCrop"))
    {            
        float4 Pos = GetCameraPos() + GetMousePos();
        int Zindex = CheckUpdateTile(Pos);
        int frame = 0;

        while (1)
        {
            if (Zindex == -1)
            {
                return;
            }

            if (Zindex != -1)
            {
                TileMap->SetTileFrame(0, Pos, 0);

                frame = TileMap->GetTile(Zindex, Pos)->GetFrame();

                if (frame >= GetLastIndexCrops(Zindex))
                {
                    return;
                }

                TileMap->SetTileFrame(Zindex, Pos, frame + 1);
            }
        }
    }
}



void Level_Farm::ImageRoad()
{

    GameEngineDirectory Dir;

    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");

    //타일
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

    {
        Dir.Move("NPC");
        GameEngineImage* MarlonRender = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Marlon.BMP"));
        Dir.MoveParent();
    }
    {
        Dir.Move("UI");
        GameEngineImage* MarlonText = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MarlonTextBox.BMP"));
        GameEngineImage* MarlonText2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MarlonTextBox2.BMP"));
        GameEngineImage* TextShadow = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TextBoxShodow.BMP"));

        GameEngineImage* SmallText = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SmallText.BMP"));
        GameEngineImage* SmallTextShadow = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SmallTextShadow.BMP"));
        Dir.MoveParent();
    }

    {
        Dir.Move("Object");
        GameEngineImage* Tree = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Tree.BMP"));
        Tree->Cut(5, 1);
        GameEngineImage* TreeUnder = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TreeUnder.BMP"));

        GameEngineImage* TreeDebris1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TreeDebris1.BMP"));
        GameEngineImage* TreeDebris2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TreeDebris2.BMP"));

        GameEngineImage* Obstacle1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Obstacle1.BMP"));
        GameEngineImage* Obstacle2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Obstacle2.BMP"));
        GameEngineImage* Obstacle3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Obstacle3.BMP"));

        GameEngineImage* SellBox = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SellBox.BMP"));
        GameEngineImage* SellBoxCover = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SellBoxCover.BMP"));
        SellBoxCover->Cut(13, 1);

       
        Dir.MoveParent();
    }

    //플레이어
    {
        GameEngineImage* Player = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Player.BMP"));
        Player->Cut(6, 21);

        GameEngineImage* Playerleft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Playerleft.BMP"));
        Playerleft->Cut(6, 21);
        GameEngineImage* Shadow = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Shadow.BMP"));

        GameEngineImage* Parsnip = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IconBranch.BMP"));

    }

    CropImageRoad();
    ToolImageRoad();
    UIImageRoad();
}

void Level_Farm::CropImageRoad()
{

    GameEngineDirectory Dir;

    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");

    //농작물
    {
        Dir.Move("Crops");

        GameEngineImage* Parsnip = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Parsnip.BMP"));
        Parsnip->Cut(6, 1);
        GameEngineImage* IconParsnip = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IconParsnip.BMP"));
        GameEngineImage* HIconParsnip = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HIconParsnip.BMP"));
        HIconParsnip->Cut(4, 1);
        GameEngineImage* SeedParsnip = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SeedParsnip.BMP"));

        GameEngineImage* Cauliflower = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Cauliflower.BMP"));
        Cauliflower->Cut(7, 1);
        GameEngineImage* IconCauliflower = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IconCauliflower.BMP"));
        GameEngineImage* HIconCauliflower = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HIconCauliflower.BMP"));
        HIconCauliflower->Cut(4, 1);
        GameEngineImage* SeedCauliflower = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SeedCauliflower.BMP"));

        GameEngineImage* Garlic = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Garlic.BMP"));
        Garlic->Cut(5, 1);
        GameEngineImage* IconGarlic = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IconGarlic.BMP"));
        GameEngineImage* HIconGarlic = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HIconGarlic.BMP"));
        HIconGarlic->Cut(4, 1);
        GameEngineImage* SeedGarlic = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SeedGarlic.BMP"));

        GameEngineImage* Bean = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Bean.BMP"));
        Bean->Cut(8, 1);
        GameEngineImage* IconBean = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IconBean.BMP"));
        GameEngineImage* HIconBean = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HIconBean.BMP"));
        HIconBean->Cut(4, 1);
        GameEngineImage* SeedBean = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SeedBean.BMP"));
    }
}
void Level_Farm::ToolImageRoad()
{

    GameEngineDirectory Dir;

    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");

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
       
        
        GameEngineImage* DHammer = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DHammer.BMP"));
        DHammer->Cut(6, 1);
        GameEngineImage* RHammer = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RHammer.BMP"));
        RHammer->Cut(6, 1);
        GameEngineImage* LHammer = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LHammer.BMP"));
        LHammer->Cut(6, 1);
        GameEngineImage* UHammer = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UHammer.BMP"));
        UHammer->Cut(6, 1);
        GameEngineImage* Hammer = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HammerIcon.BMP"));

        GameEngineImage* Default = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Default.BMP"));
    }
}
void Level_Farm::UIImageRoad()
{
    GameEngineDirectory Dir;

    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");

    {
        Dir.Move("InfoBox");
        GameEngineImage* InfoAxe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoAxeIcon.BMP"));
        GameEngineImage* InfoHoe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoHoeIcon.BMP"));
        GameEngineImage* InfoWatering = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoWateringIcon.BMP"));
        GameEngineImage* InfoPick = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoPickIcon.BMP"));
        GameEngineImage* InfoHammer = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoHammerIcon.BMP"));

        GameEngineImage* InfoSeedParsnip = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoSeedParsnip.BMP"));
        GameEngineImage* InfoSeedBean = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoSeedBean.BMP"));
        GameEngineImage* InfoSeedGarlic = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoSeedGarlic.BMP"));
        GameEngineImage* InfoSeedCauliflower = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoSeedCauliflower.BMP"));

        GameEngineImage* InfoIconParsnip = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoIconParsnip.BMP"));
        GameEngineImage* InfoIconBean = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoIconBean.BMP"));
        GameEngineImage* InfoIconGarlic = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoIconGarlic.BMP"));
        GameEngineImage* InfoIconCauliflower = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoIconCauliflower.BMP"));
       
        GameEngineImage* InfoIconStone = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoIconStone.BMP"));
        GameEngineImage* InfoIconTopaz = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoIconTopaz.BMP"));
        GameEngineImage* InfoIconIron = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoIconIron.BMP"));

        GameEngineImage* InfoIconBranch = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InfoIconBranch.BMP"));

        Dir.MoveParent();
    }
}