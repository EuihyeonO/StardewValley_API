#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineActor.h"

// 제약사항
// 이 액터는 무조건 0,0,0
// 각층을 세팅할때는 무조건 cutting된 이미지만 들어올수 있다.

struct FloorInfo
{

};

// 설명 :
class GameEngineCollision;
class GameEngineTileMap : public GameEngineActor
{
public:
    // constrcuter destructer
    GameEngineTileMap();
    ~GameEngineTileMap();

    // delete Function
    GameEngineTileMap(const GameEngineTileMap& _Other) = delete;
    GameEngineTileMap(GameEngineTileMap&& _Other) noexcept = delete;
    GameEngineTileMap& operator=(const GameEngineTileMap& _Other) = delete;
    GameEngineTileMap& operator=(GameEngineTileMap&& _Other) noexcept = delete;

    // 무조건 
    void CreateTileMap(int _X, int _Y, int _Z, int _Order, float4 _TileSize);

    void CreateTileMapCollision(int _X, int _Y, int _Z, int _Order, float4 _TileSize);

    void SetFloorSetting(int _ZIndex, const std::string_view& _ImageName);

    void SetTileFrame(int _ZIndex, float4 _Pos, int _ImageFrame);

    void SetTileFrame(int _ZIndex, int _X, int _Y, int _ImageFrame);

    float4 ConvertIndexToTilePosition(float4 Pos);

    float4 ConvertIndexToTilePosition(int _X, int _Y);

    int GetTileFrame(int _ZIndex, float4 _Pos);

    GameEngineRender* GetTile(int _ZIndex, float4 _Pos);

    GameEngineCollision* GetTileCollision(int _ZIndex, float4 _Pos);

    bool IsValidIndex(int _Z, int _Y, int _X);

    float4 GetIndex(float4 _Pos);

protected:

private:
    float4 ScreenSize = float4::Zero;
    float4 TileScale = float4::Zero;

    int X = -1;
    int Y = -1;
    int Z = -1;

    std::vector<std::string_view> FloorImageName;
    std::vector<std::vector<std::vector<GameEngineRender*>>> TileRenders;
    std::vector<std::vector<std::vector<GameEngineCollision*>>> TileCollision;
};

