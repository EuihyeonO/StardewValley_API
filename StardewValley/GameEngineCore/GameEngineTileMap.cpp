#include "GameEngineTileMap.h"
#include "GameEngineRender.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineResources.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

GameEngineTileMap::GameEngineTileMap()
{
}

GameEngineTileMap::~GameEngineTileMap()
{
}

void GameEngineTileMap::CreateTileMap(int _X, int _Y, int _Z, int _Order, float4 _TileSize)
{
    float4 ScreenSize = GameEngineWindow::GetScreenSize();

    TileScale = _TileSize;

    TileRenders.resize(_Z);
    FloorImageName.resize(_Z);

    X = _X;
    Y = _Y;
    Z = _Z;

    for (size_t z = 0; z < _Z; z++)
    {
        TileRenders[z].resize(_Y);

        for (size_t y = 0; y < _Y; y++)
        {
            TileRenders[z][y].resize(_X);

            for (size_t x = 0; x < _X; x++)
            {
                GameEngineRender* Render = CreateRender();

                float4 TilePos = _TileSize;
                TilePos.x *= x;
                TilePos.y *= y;
                TilePos.x += _TileSize.hx();
                TilePos.y += _TileSize.hy();
                Render->SetPosition(TilePos);
                Render->SetScale(TileScale);
                Render->SetOrder(_Order + _Z);
                Render->Off();
                TileRenders[z][y][x] = Render;
            }
        }
    }
}

void GameEngineTileMap::CreateTileMapCollision(int _X, int _Y, int _Z, int _Order, float4 _TileSize)
{
    float4 ScreenSize = GameEngineWindow::GetScreenSize();

    TileScale = _TileSize;

    TileCollision.resize(_Z);
    FloorImageName.resize(_Z);

    X = _X;
    Y = _Y;
    Z = _Z;

    for (size_t z = 0; z < _Z; z++)
    {
        TileCollision[z].resize(_Y);

        for (size_t y = 0; y < _Y; y++)
        {
            TileCollision[z][y].resize(_X);

            for (size_t x = 0; x < _X; x++)
            {
                GameEngineCollision* Collision = CreateCollision();

                float4 TilePos = _TileSize;
                TilePos.x *= x;
                TilePos.y *= y;
                TilePos.x += _TileSize.hx();
                TilePos.y += _TileSize.hy();
                Collision->SetPosition(TilePos);
                Collision->SetScale(TileScale);
                Collision->SetOrder(_Order + _Z);
                Collision->Off();
                TileCollision[z][y][x] = Collision;
            }
        }
    }
}

void GameEngineTileMap::SetFloorSetting(int _ZIndex, const std::string_view& _ImageName)
{
    if (TileRenders.size() <= _ZIndex)
    {
        MsgAssert("타일을 만들고 floor 이상의 세팅을 하려고 했습니다.");
        return;
    }

    GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_ImageName);

    if (nullptr == Image)
    {
        MsgAssert("존재하지 않는 이미지로 floor를 세팅할수 없습니다.");
    }

    if (false == Image->IsImageCutting())
    {
        MsgAssert("자르지 않은 이미지는 타일맵에 세팅될 수 없습니다.");
    }

    FloorImageName[_ZIndex] = _ImageName;

    std::vector<std::vector<GameEngineRender*>>& FloorRenders = TileRenders[_ZIndex];

    for (size_t y = 0; y < FloorRenders.size(); y++)
    {
        std::vector<GameEngineRender*>& XLineRenders = FloorRenders[y];

        for (size_t x = 0; x < XLineRenders.size(); x++)
        {
            GameEngineRender* Render = XLineRenders[x];
            // Render->On();
            Render->SetImage(_ImageName);
        }
    }

}

void GameEngineTileMap::SetTileFrame(int _ZIndex, float4 _Pos, int _ImageFrame)
{

    float4 Index = GetIndex(_Pos);

    SetTileFrame(_ZIndex, Index.ix(), Index.iy(), _ImageFrame);
}

void GameEngineTileMap::SetTileFrame(int _ZIndex, int _X, int _Y, int _ImageFrame)
{
    IsValidIndex(_ZIndex, _Y, _X);

    std::vector<std::vector<GameEngineRender*>>& FloorRenders = TileRenders[_ZIndex];
    // 캐칭
    GameEngineRender* TileRender = FloorRenders[_Y][_X];

    // operator[]

    TileRender->On();
    TileRender->SetFrame(_ImageFrame);

    return;
}

float4 GameEngineTileMap::ConvertIndexToTilePosition(float4 _Pos)
{
    float4 Index = GetIndex(_Pos);
    return ConvertIndexToTilePosition(Index.ix(), Index.iy());
}

float4 GameEngineTileMap::ConvertIndexToTilePosition(int _X, int _Y)
{
    return float4(_X * TileScale.x + TileScale.hx(), _Y * TileScale.y + TileScale.hy(), 0.0f, 0.0f) + GetPos();
}

int GameEngineTileMap::GetTileFrame(int _ZIndex, float4 _Pos)
{

    float4 Index = GetIndex(_Pos);

    IsValidIndex(_ZIndex, Index.iy(), Index.ix());

    std::vector<std::vector<GameEngineRender*>>& FloorRenders = TileRenders[_ZIndex];

    GameEngineRender* TileRender = FloorRenders[Index.iy()][Index.ix()];

    if (false == TileRender->IsUpdate())
    {
        return -1;
    }

    return TileRender->GetFrame();
}

bool GameEngineTileMap::IsValidIndex(int _Z, int _Y, int _X)
{
    if (TileRenders.size() <= _Z)
    {
        MsgAssert("Z인덱스가 오버했습니다.");
        return false;
    }

    if (TileRenders[_Z].size() <= _Y)
    {
        MsgAssert("Y인덱스가 오버했습니다.");
        return false;
    }

    if (TileRenders[_Z][_Y].size() <= _X)
    {
        MsgAssert("X인덱스가 오버했습니다.");
        return false;
    }

    return true;
}

float4 GameEngineTileMap::GetIndex(float4 _Pos)
{
    float4 Index = _Pos - GetPos();
    Index.x /= TileScale.x;
    Index.y /= TileScale.y;

    return Index;
}

GameEngineRender* GameEngineTileMap::GetTile(int _ZIndex, float4 _Pos)
{
    float4 Index = GetIndex(_Pos);

    IsValidIndex(_ZIndex, Index.iy(), Index.ix());

    return TileRenders[_ZIndex][Index.iy()][Index.ix()];
}

GameEngineCollision* GameEngineTileMap::GetTileCollision(int _ZIndex, float4 _Pos)
{
    float4 Index = GetIndex(_Pos);

    IsValidIndex(_ZIndex, Index.iy(), Index.ix());

    return TileCollision[_ZIndex][Index.iy()][Index.ix()];
}