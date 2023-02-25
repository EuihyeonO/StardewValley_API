#include "Pierre.h"
#include "ContentsEnum.h"
#include "globalValue.h"
#include "Player.h"
#include "Inventory.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/Button.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/NumberRenderObject.h>

#include <vector>

std::map<std::string, Button*> Pierre::ShopItemList;
bool Pierre::isOpenShop = false;

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

    PierreInventory = GetLevel()->CreateActor<Inventory>();
    PierreInventory->SetOwnerToPierre();
    PierreInventory->Off();

    PierreCollision = CreateCollision(ActorType::NPC);
    PierreCollision->SetScale(PierreRender->GetScale());
    PierreCollision->SetPosition({ 1430, 723 });

    ShopRender = CreateRender("Shop.bmp", 200);
    ShopRender->SetScaleToImage();
    ShopRender->Off();

    AddItemToShop("ItemParsnip.bmp");
    AddItemToShop("ItemCauliflower.bmp");
    AddItemToShop("ItemGarlic.bmp");
    AddItemToShop("ItemBean.bmp");

    MoneyRender.SetOwner(this);
    MoneyRender.SetImage("NumberBig.bmp", { 18,24 }, 250, RGB(134, 134, 134), "NumberBig.bmp");
    MoneyRender.SetValue(globalValue::GetMoney());
    MoneyRender.SetAlign(Align::Right);
    MoneyRender.SetCameraEffect(false);
    MoneyRender.SetRenderPos({ 476, 457 });
    MoneyRender.Off();
}

void Pierre::Update(float _DeltaTime)
{   
    SortToShopItem();
    MoneyRender.SetValue(globalValue::GetMoney());
}

void Pierre::Render(float _Time)
{
    if (GameEngineInput::IsDown("Debug"))
    {
        if (isDebug == false)
        {
            isDebug = true;
        }
        else
        {
            isDebug = false;
        }
    }

    if (isDebug == true)
    {
        HDC _hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();

        Rectangle(_hdc, PierreCollision->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - PierreCollision->GetScale().hix(),
            PierreCollision->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - PierreCollision->GetScale().hiy(),
            PierreCollision->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + PierreCollision->GetScale().hix(),
            PierreCollision->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + PierreCollision->GetScale().hiy());
    }
}

void Pierre::OpenPierreShop()
{

    bool isCollision = PierreCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::Player) , .TargetColType = CT_Rect, .ThisColType = CT_Rect });
   
    if (false == isCollision)
    {
        return;
    }

    if (true == isCollision)
    {
        if (isOpenShop ==false)
        {
            Player::ChangePlayerIdle(Player::GetPlayer()->GetDir());
            ShopRender->SetPosition(GetLevel()->GetCameraPos() + GameEngineWindow::GetScreenSize().half());
            ShopRender->On();
            AllShopItemOnOff();

            isOpenShop = true;

            PierreInventory->SetItemPos();
            PierreInventory->On();
            PierreInventory->AllItemOn();  
            MoneyRender.On();            
        }

        else if (isOpenShop = true)
        {
            isOpenShop = false;

            Player::ChangePlayerIdle(Player::GetPlayer()->GetDir());
            PierreInventory->AllItemOff();
            PierreInventory->Off();
            MoneyRender.Off();
            ShopRender->Off();
            AllShopItemOnOff();
        }
    }
}

void CreateItem(Button* _button)
{
    std::string ItemName = Pierre::GetNameShopItem(_button);
       
    int Price = Item::GetSeedPrice(ItemName);
    int Money = globalValue::GetMoney();
    
    if(Money < Price)
    {
        return;
    }
    
    globalValue::PlusToMoney(-Price);
    globalValue::CreateItemToAllInventory(ItemName, static_cast<int>(ItemType::Seed));

}

void Pierre::AddItemToShop(std::string _Name)
{
    size_t NameSize = _Name.size();
    
    std::string PureName = _Name.substr(4, NameSize - 4);

    ShopItemList.insert({ PureName, GetLevel()->CreateActor<Button>()});
    ShopItemList[PureName]->SetReleaseImage(_Name);
    ShopItemList[PureName]->SetHoverImage("Hover" + _Name);
    ShopItemList[PureName]->SetPressImage("Hover" + _Name);
    ShopItemList[PureName]->SetScale({ 812, 82 });
    ShopItemList[PureName]->SetRenderOrder(201);
    ShopItemList[PureName]->SetTargetCollisionGroup(static_cast<int>(ActorType::Mouse));
    ShopItemList[PureName]->GetButtonRender()->OnOffSwtich();
    ShopItemList[PureName]->SetClickCallBack(CreateItem);

    if (ShopItemList.size() == 1)
    {
        SelectedItem = ShopItemList[PureName];
    }
}

void Pierre::SortToShopItem()
{
    std::map<std::string, Button*>::iterator startiter = ShopItemList.begin();
    std::map<std::string, Button*>::iterator enditer = ShopItemList.end();

    for (int count = 0; startiter != enditer && count < 4; startiter++, count++)
    {
        startiter->second->SetPos(ShopRender->GetPosition() + ShopTopPos + float4{ 0, float(count * 82) });
    }
}

void Pierre::AllShopItemOnOff()
{
    std::map<std::string, Button*>::iterator startiter = ShopItemList.begin();
    std::map<std::string, Button*>::iterator enditer = ShopItemList.end();

    for (int count = 0; startiter != enditer && count<4; startiter++, count++)
    {
        startiter->second->GetButtonRender()->OnOffSwtich();
    }
}

std::string Pierre::GetNameShopItem(Button* _Item)
{
    std::map<std::string, Button*>::iterator startiter = ShopItemList.begin();
    std::map<std::string, Button*>::iterator enditer = ShopItemList.end();

    for (int count = 0; startiter != enditer && count < 4; startiter++, count++)
    {
        if (startiter->second == _Item)
        {
            return "Seed" + startiter->first;
        }
    }

    return "";
}

void Pierre::ShopOff()
{
    PierreInventory->AllItemOff();
}