#pragma once

#include <string_view>

#include <GameEngineCore/GameEngineActor.h>

class Item : public GameEngineActor
{

public:

	Item();
	~Item();

    void SetItemInfo(std::string_view _ItemName);
    void SetItemPos();

    GameEngineRender* GetItemRender()
    {
        return RenderImage;
    }

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
    std::string ItemName;
    
    int ItemType = 0;
    int ItemOrder = 0;
};

