#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Crops.h"
#include "Player.h"
#include "ContentsEnum.h"

Crops::Crops()
{
    SetPos(Player::GetPlayer()->GetPos());  
}

Crops::~Crops()
{
}

void Crops::Start()
{          
}

void Crops::CollisionOn()
{
    CollisionImage->On();
}
void Crops::CollisionOff()
{
    CollisionImage->Off();
}

bool Crops::IsCollisionUpdate()
{
    if(CollisionImage != nullptr)
    {
        return CollisionImage->IsUpdate();
    }

    return false;
}

void Crops::Update(float _DeltaTime)
{
    if (CropName != "0" && isSetting != true)
    {
        Image = CreateRender(CropName + ".bmp", 1);
        Image->SetScale({ 64,64 });
        CollisionImage = CreateCollision(ActorType::Crops);
        CollisionImage->SetScale({ 64,64 });

        isSetting = true;
    }


}

void Crops::Render(float _Time)
{
}

void Crops::GrowUp()
{
    if (life <= 0)
    {
        return;
    }

    --life;
    Image->SetFrame(5 - life);
}

void Crops::SetCrops()
{
    Image = CreateRender(CropName + ".bmp", 5);
    Image->SetScale({ 64,64 });
    CollisionImage = CreateCollision(ActorType::Crops);
    CollisionImage->SetScale({ 64,64 });
}

void Crops::SetName(std::string _Name)
{
    CropName = _Name;
}
