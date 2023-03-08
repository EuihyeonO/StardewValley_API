#pragma once

#include <string_view>
#include <string>

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/NumberRenderObject.h>

class GameEngineCollision;
class Item : public GameEngineActor
{

public:

	Item();
	~Item();

    void ItemInit(std::string_view& _ItemName, int ItemType);
    void SetItemRender(std::string_view& _ItemName);

    float4 GetItemRenderPos()
    {
        return RenderImage->GetPosition();
    }

    std::string GetItemName()
    {
        return ItemName;
    }

    void PlusQuntity()
    {
        ++Quantity;
    }

    void MinusQuntity()
    {
        --Quantity;
    }
    
    static int GetSeedPrice(std::string& _ItemName);

    int GetQuantity()
    {
        return Quantity;
    }

    int GetItemType()
    {
        return Itemtype;
    }

    int GetSeedFloor();

    GameEngineRender* GetRenderImage()
    {
        return RenderImage;
    }

    bool GetIsHarvested()
    {
        return isHarvested;
    }

    void RenderHarvesting();

    bool isAbleToSell();

    void UpdatePos();
    void InfoBoxOnOff();
    void InitPrice();
    bool isCollisionToMouse();

    void SetIsHarvestied()
    {
        isHarvested = true;
    }

    void SetIsHarvestedToFalse()
    {
        isHarvested = false;
    }

    int GetPrice()
    {
        return Price;
    }

	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

    void UpdateQuantity();

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:
    GameEngineRender* RenderImage =  nullptr;
    GameEngineRender* InfoRenderImage =  nullptr;
    GameEngineRender* SelectedLine =  nullptr;
    GameEngineRender* QuantityText = nullptr;

    GameEngineCollision* ItemCollision = nullptr;

    
    std::string ItemName;    

    NumberRenderObject QuantityRender;

    int Itemtype = 0;
    int Quantity = 1;
    int Price = 0;

    bool isHarvested = false;

    GameEngineRender* CopyImage = nullptr;
};

