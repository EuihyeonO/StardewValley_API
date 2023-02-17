#include "Pierre.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <vector>

Pierre::Pierre()
{  
}

Pierre::~Pierre()
{
}

void Pierre::Start()
{
    PierreRender = CreateRender("Pierre.bmp", 45);
    PierreRender->SetScaleToImage();
    PierreRender->SetPosition({ 1430, 723 });

    PierreCollision = CreateCollision(ActorType::NPC);
    PierreCollision->SetScale(PierreRender->GetScale());
    PierreCollision->SetPosition({ 1430, 723 });

    ShopRender = CreateRender("Shop.bmp", 200);
    ShopRender->SetScaleToImage();
    ShopRender->Off();

    AddItemToShop("ParsnipItem.bmp");
}

void Pierre::Update(float _DeltaTime)
{   
    OpenPierreShop();
    SortToShopItem();
}

void Pierre::Render(float _Time)
{

}

void Pierre::OpenPierreShop()
{
    std::vector<GameEngineCollision*> Collisions;

    if (true == PierreCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::Player) , .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collisions))
    {
        if (GameEngineInput::IsDown("Interact") == true)
        {
            ShopRender->SetPosition(GetLevel()->GetCameraPos() + GameEngineWindow::GetScreenSize().half());
            ShopRender->On();
        }
    }
}

void Pierre::AddItemToShop(std::string _Name)
{
    ShopItemList.insert({ _Name, CreateRender(_Name, 201) });
    ShopItemList[_Name]->SetScaleToImage();
}

void Pierre::SortToShopItem()
{
    ShopItemList["ParsnipItem.bmp"]->On();
    ShopItemList["ParsnipItem.bmp"]->SetPosition(ShopRender->GetPosition() + float4{119, -271});
}
