#include "GameEngineTileMap.h"
#include "GameEngineRender.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineResources.h"
#include <GameEngineCore/GameEngineRender.h>

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
    std::vector<std::vector<GameEngineRender*>>& FloorRenders = TileRenders[_ZIndex];

    float4 Index = _Pos;
    Index.x /= TileScale.x;
    Index.y /= TileScale.y;

    // 캐칭
    GameEngineRender* TileRender = FloorRenders[Index.iy()][Index.ix()];

    // operator[]

    TileRender->On();
    TileRender->SetFrame(_ImageFrame);

    return;
}

int GameEngineTileMap::GetTileFrame(int _ZIndex, float4 _Pos) 
{
    std::vector<std::vector<GameEngineRender*>>& FloorRenders = TileRenders[_ZIndex];

    float4 Index = _Pos;
    Index.x /= TileScale.x;
    Index.y /= TileScale.y;

    GameEngineRender* TileRender = FloorRenders[Index.iy()][Index.ix()];

    if (false == TileRender->IsUpdate())
    {
        return -1;
    }

    return TileRender->GetFrame();
}


GameEngineRender* GameEngineTileMap::GetTile(int _ZIndex, float4 _Pos)
{
    float4 Index = _Pos;
    Index.x /= TileScale.x;
    Index.y /= TileScale.y;

    return TileRenders[_ZIndex][Index.iy()][Index.ix()];
}


void GameEngineTileMap::AllTileMove(int _ZIndex, float4 _Pos)
{
    for (int y = 0; y < Y; y++)
    {
        for (int x = 0; x < X; x++)
        {
            float4 CurPos = TileRenders[_ZIndex][y][x]->GetPosition();
            TileRenders[_ZIndex][y][x]->SetPosition(CurPos + _Pos);
        }
    }
}

