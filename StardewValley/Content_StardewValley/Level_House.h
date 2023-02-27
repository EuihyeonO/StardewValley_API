#pragma once
#include "Player.h"
#include "Inventory.h"

#include <GameEngineCore/GameEngineLevel.h>

class UI;
class House;
class Level_House : public GameEngineLevel

{

public:
    void ImageRoad();
	Level_House();
	~Level_House();

	Level_House(const Level_House& _Other) = delete;
	Level_House(Level_House&& _Other) noexcept = delete;
	Level_House& operator=(const Level_House& _Other) = delete;
	Level_House& operator=(Level_House&& _Other) noexcept = delete;

    static Inventory* HouseInventory; 
    static UI* HouseUI;

protected:
    void Loading() override;
    void Update(float _DeltaTime) override;
    void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
    void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:

    Player* HousePlayer = nullptr;  
    House* HouseController = nullptr;
};

