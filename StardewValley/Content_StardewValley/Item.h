#pragma once

#include <string_view>

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>

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

    bool GetIsHarvesting()
    {
        return isHarvesting;
    }

    void SetItemisHarvesting();

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
    GameEngineRender* SelectedLine =  nullptr;
    GameEngineRender* QuantityText = nullptr;
    
    std::string ItemName;    

   
    int Itemtype = 0;
    int Quantity = 1;

    bool isHarvesting = false;

    GameEngineRender* CopyImage = nullptr;
};

