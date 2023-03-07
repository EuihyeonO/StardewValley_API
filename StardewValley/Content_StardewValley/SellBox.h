#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <string>

class Inventory;
class GameEngineRender;
class GameEngineCollision;
class SellBox : public GameEngineActor
{

public:
    static Inventory* GetSellBoxInventory()
    {
        return BoxInventory;
    }

    static bool IsBOxOn();

    void BoxOn();
    void BoxOff();
    void BoxOnOff();

	SellBox();
	~SellBox();

	SellBox(const SellBox& _Other) = delete;
	SellBox(SellBox&& _Other) noexcept = delete;
	SellBox& operator=(const SellBox& _Other) = delete;
	SellBox& operator=(SellBox&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:

    GameEngineRender* SellBoxRender = nullptr;
    GameEngineRender* SellBoxCoverRender = nullptr;
    
    GameEngineCollision* SellBoxCollision = nullptr;

    GameEngineRender* SellBoxInventoryRender = nullptr;
    GameEngineRender* SelectedItem = nullptr;

    static Inventory* BoxInventory;

    bool isOnSound = false;
};

