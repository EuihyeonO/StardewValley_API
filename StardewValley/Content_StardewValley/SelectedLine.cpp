#include "SelectedLine.h"
#include "Level_Farm.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineTileMap.h>

GameEngineRender* SelectedLine::SelectedLineRender = nullptr;

SelectedLine::SelectedLine()
{
}

SelectedLine::~SelectedLine()
{
}

void SelectedLine::Start()
{
    SetPos({ 0,0 });

    SelectedLineRender = CreateRender("SelectedLine.bmp", 40);
    SelectedLineRender->SetScale({ 64,64 });
    SelectedLineRender->Off();
}

void SelectedLine::Update(float _DeltaTime)
{

}

void SelectedLine::Render(float _Time) 
{

}

void SelectedLine::LineOn()
{
     SelectedLineRender->On();
}

void SelectedLine::LineOff()
{
    SelectedLineRender->Off();
}

void SelectedLine::SetLinePos(float4 _pos)
{
    float4 Pos = Level_Farm::GetTileMap()->GetTile(0,_pos)->GetPosition();
    SelectedLineRender->SetPosition(Pos);
}

bool SelectedLine::IsLineOn()
{
    return SelectedLineRender->IsUpdate();
}