#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Player.h"
#include "ContentsEnum.h"
#include "Inventory.h"


Player* Player::MyPlayer = nullptr;

Player::Player()
{
    MyPlayer = this;
}

Player::~Player()
{
    std::map<std::string, GameEngineRender*>::iterator StartIter = Tool.begin();
    std::map<std::string, GameEngineRender*>::iterator EndIter = Tool.end();

    for (; StartIter != EndIter; StartIter++)
    {
        //delete StartIter->second;
    }
}

void Player::Start()
{
    InitPlayer();
    InitTool();
    CreatePlayerKey();
    CreateAllAnimation();
}

void Player::Update(float _DeltaTime)
{ 
    ActingUpdate(_DeltaTime);
}

void Player::Render(float _Time)
{
    //HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
    //float4 ActorPos = GetPos();

    //Rectangle(DoubleDC,
    //    640 - 5,
    //    360 - 5,
    //    640 + 5,
    //    360 + 5
    //);
}
