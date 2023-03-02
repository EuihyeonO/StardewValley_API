#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class AffectionBox;
class MenuButton;
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
    static void SetTileObject();
    static void SetMineralToTile(int _Num, const std::string_view& _ImageName);
    static int CheckUpdateTile(float4 _pos);
    static bool isCollisionToTile(float4 _pos);
    static bool isToolCollisionToTile();
    static void DeleteTile();

    void GetMineral(int _MineralName);
    void CreateTileAnimation(int _MinaralName, const std::string_view& _ImageName);
    void BreakStone(int _floor, float4 _pos);
    void ImageRoad();
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
    static int isFirst;

    AffectionBox* MineAffectionBox = nullptr;
    Player* MinePlayer = nullptr;
    Mine* MineController = nullptr;
    MenuButton* MineMenuButton = nullptr;

};


