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

    static void SubToStoneLife(float4 _pos);
    void SetTileObject();

    void ImageRoad();

    static bool isCollisionToTile(float4 _pos);
    static bool isToolCollisionToTile();
    int CheckUpdateTile(float4 _pos);
    void BreakStone(int _floor, float4 _pos);
    void TileUpdate();

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
    static GameEngineTileMap* MineTileMap;
    static std::vector<GameEngineCollision*> OnCollisionList;
    static std::vector<std::vector<int>> StoneLife;    
    Player* MinePlayer = nullptr;
    Mine* MineController = nullptr;

};

