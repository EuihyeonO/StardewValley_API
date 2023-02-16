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

    void SetFloorSetting(int _ZIndex, const std::string_view& _ImageName);

    void SetTileFrame(int _ZIndex, float4 _Pos, int _ImageFrame);

    int GetTileFrame(int _ZIndex, float4 _Pos);

    GameEngineRender* GetTile(int _ZIndex, float4 _Pos);
    void AllTileMove(int _ZIndex, float4 _Pos);

protected:

private:
    float4 ScreenSize;
    float4 TileScale;

    int X;
    int Y;
    int Z;

    std::vector<std::string_view> FloorImageName;
    std::vector<std::vector<std::vector<GameEngineRender*>>> TileRenders;
};

