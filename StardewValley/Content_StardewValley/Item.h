#pragma once

#include <string_view>

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>

class Item : public GameEngineActor
{

public:

	Item();
    Item(std::string_view& _ItemName);
	~Item();

    void ItemInit(std::string_view& _ItemName);
    void SetItemRender(GameEngineRender* _Render);
    void SetItemPos();

    float4 GetItemRenderPos()
    {
        return RenderImage->GetPosition();
    }

    std::string GetItemName()
    {
        return ItemName;
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

private:
    GameEngineRender* RenderImage =  nullptr;
    GameEngineRender* SelectedLine =  nullptr;
    
    
    std::string ItemName;    
    size_t ItemOrder = 0;
   
    int ItemType = 0;
};

