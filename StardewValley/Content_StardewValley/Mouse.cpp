#include "Mouse.h"
#include "ContentsEnum.h"
#include "SelectedLine.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::Start()
{
    GameEngineRender* render = CreateRender("Cursor.bmp", 205);
    render->SetScaleToImage();
    CursorScale = render->GetScale();
    render->SetPosition(CursorScale.half());
    ColMap = GameEngineResources::GetInst().ImageFind("FarmC.bmp");
    GameEngineCollision* collision = CreateCollision(static_cast<int>(ActorType::Mouse));
    SetPos(GetLevel()->GetMousePosToCamera());
    collision->SetPosition(float4{-20,-20 });
    ShowCursor(false);

    collision->SetScale({ 5, 5 });

}

void Mouse::Update(float _DeltaTime)
{
    SetPos(GetLevel()->GetMousePosToCamera());
    SelectedTileOnOff();
}

void Mouse::Render(float _Time)
{

}


void Mouse::SelectedTileOnOff()
{
    if (GetLevel()->GetName() != "Farm")
    {
        return;
    }

    if (nullptr != ColMap && RGB(255, 0, 255) != ColMap->GetPixelColor(GetPos(), RGB(255, 0, 255)))
    {
        SelectedLine::LineOff();
    }

    if (nullptr != ColMap && RGB(255, 0, 255) == ColMap->GetPixelColor(GetPos(), RGB(255, 0, 255)))
    {
        float4 Pos = GetPos();
        SelectedLine::LineOn();
        SelectedLine::SetLinePos(Pos);
    }
}

