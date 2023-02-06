#include "GameEngineComponent.h"
#include "GameEngineActor.h"

GameEngineComponent::GameEngineComponent()
{
}

GameEngineComponent::~GameEngineComponent()
{
}

GameEngineActor* GameEngineComponent::GetActor()
{
    return GetOwner<GameEngineActor>();
}

float4 GameEngineComponent::GetActorPlusPos()
{
    return GetActor()->GetPos() + Position;
}