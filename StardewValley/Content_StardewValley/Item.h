#pragma once

#include <string_view>

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>

class Item : public GameEngineActor
{

public:

	Item();
	~Item();

    void ItemInit(std::string_view& _ItemName);
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

    int GetQuantity()
    {
        return Quantity;
    }

    void SelectedLineRender();

    GameEngineRender* GetRenderImage()
    {
        return RenderImage;
    }

	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:
    GameEngineRender* RenderImage =  nullptr;
    GameEngineRender* SelectedLine =  nullptr;
    
    
    std::string ItemName;    
    size_t ItemOrder = 0;
   
    int ItemType = 0;
    int Quantity = 1;
};

