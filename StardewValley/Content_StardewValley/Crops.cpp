#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Crops.h"
#include "Player.h"
#include "ContentsEnum.h"

Crops::Crops()
{
}

Crops::~Crops()
{
}

void Crops::Start()
{   
}

void Crops::Update(float _DeltaTime)
{
}

void Crops::Render(float _Time)
{
}

void Crops::InitCrop(std::string _Name, float4 _Pos)
{
    Image = CreateRender(_Name, 1);
    Image->SetPosition(_Pos);
    Image->SetScale({64,64});
}
