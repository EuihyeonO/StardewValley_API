#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Player.h"
#include "ContentsEnum.h"
#include "Inventory.h"
#include "Crops.h"
#include "Level_Farm.h"


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

    ColBody = CreateCollision(ActorType::Player);
    ColBody->SetScale({ 50,50 });
}

void Player::Update(float _DeltaTime)
{ 
    ActingUpdate(_DeltaTime);
    InteractToCrops();  

    dynamic_cast<Level_Farm*>(GetLevel())->CreateCrops("Parsnip");
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
