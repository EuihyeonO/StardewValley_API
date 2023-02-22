#include "Mouse.h"
#include "ContentsEnum.h"
#include "SelectedLine.h"
#include "Player.h"
#include "Level_Farm.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineTileMap.h>

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::Start()
{
    GameEngineRender* render = CreateRender("Cursor.bmp", 300);
    render->SetScaleToImage();
    CursorScale = render->GetScale();
    render->SetPosition(CursorScale.half());

    if (GetLevel()->GetName() == "Farm")
    {
        ColMap = GameEngineResources::GetInst().ImageFind("FarmC.bmp");
    }

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
        float4 MousePos = GetPos();
        float4 PlayerPos = Player::GetPlayer()->GetPos();

        float distance = sqrt((MousePos.x - PlayerPos.x) * (MousePos.x - PlayerPos.x) + (MousePos.y - PlayerPos.y) * (MousePos.y - PlayerPos.y));      

        if (distance<=112 && Player::GetPlayer()->isFront(MousePos) == true)
        {
            SelectedLine::LineOn();
            SelectedLine::SetLinePos(MousePos);
        }
        else
        {
            SelectedLine::LineOff();
        }
    }
}


