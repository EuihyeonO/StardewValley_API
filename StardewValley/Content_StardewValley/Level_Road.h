#pragma once
#include "Player.h"
#include "Inventory.h"

#include <GameEngineCore/GameEngineLevel.h>


class GameEngineCollision;
class Inventory;
class Player;
class Level_Road : public GameEngineLevel
{

public:
    static Inventory* RoadInventory;

	Level_Road();
	~Level_Road();

	Level_Road(const Level_Road& _Other) = delete;
	Level_Road(Level_Road&& _Other) noexcept = delete;
	Level_Road& operator=(const Level_Road& _Other) = delete;
	Level_Road& operator=(Level_Road&& _Other) noexcept = delete;

protected:
    void Loading() override;
    void Update(float _DeltaTime) override;
    void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
    void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:  

    Player* RoadPlayer = nullptr;
};

