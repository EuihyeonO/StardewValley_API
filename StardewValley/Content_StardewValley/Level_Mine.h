#pragma once
#include <GameEngineCore/GameEngineLevel.h>


class UI;
class Inventory;
class Player;
class Mine;
class GameEngineTileMap;
class Level_Mine : public GameEngineLevel
{

public:
    static Inventory* MineInventory;

    void ImageRoad();

    void SetTileObject();
	
    Level_Mine();
	~Level_Mine();

	Level_Mine(const Level_Mine& _Other) = delete;
	Level_Mine(Level_Mine&& _Other) noexcept = delete;
	Level_Mine& operator=(const Level_Mine& _Other) = delete;
	Level_Mine& operator=(Level_Mine&& _Other) noexcept = delete;

protected:
    void Loading() override;
    void Update(float _DeltaTime) override;
    void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
    void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
private:
    static UI* MineUI;

    Player* MinePlayer = nullptr;
    Mine* MineController = nullptr;

    GameEngineTileMap* MineTileMap = nullptr;
};

