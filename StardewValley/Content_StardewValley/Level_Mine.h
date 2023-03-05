#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Mummy;
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
    static Level_Mine* GetLevelMineController()
    {
        return LevelMineController;
    }

    std::vector<GameEngineCollision*> GetOnCollisionList()
    {
        return OnCollisionList;
    }

    static Inventory* MineInventory;


    void SubToStoneLife(float4 _pos);
    void SetTileObject();
    void SetMineralToTile(int _Num);
    void SetMonster(Mummy* _Mummy);
    void DeleteMummyToLst(Mummy* _Mummy);
    int CheckUpdateTile(float4 _pos);
    bool isCollisionToTile(float4 _pos);
    bool isToolCollisionToTile();
    void DeleteTile();

    void GetMineral(int _MineralName);
    void CreateTileAnimation(int _MinaralName, const std::string_view& _ImageName);
    void BreakStone(int _floor, float4 _pos);
    void ImageRoad();
    void TileUpdate();

    void CreateMummy();

    static void SubNumOfMummy()
    {
       --NumOfMummy;
    }

    std::vector<Mummy*> GetMummyList()
    {
        return MummyList;
    }

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
    static Level_Mine* LevelMineController;

    static UI* MineUI;
    static GameEngineTileMap* MineTileMap;
    static std::vector<GameEngineCollision*> OnCollisionList;
    static std::vector<std::vector<int>> StoneLife; 
    static int isFirst;

    AffectionBox* MineAffectionBox = nullptr;
    Player* MinePlayer = nullptr;
    Mine* MineController = nullptr;
    MenuButton* MineMenuButton = nullptr;

    std::vector<Mummy*> MummyList;

    static int NumOfMineral;
    static int NumOfMummy;
};


