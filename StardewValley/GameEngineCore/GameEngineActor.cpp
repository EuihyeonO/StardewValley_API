#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
    for (GameEngineRender* _Render : RenderList)
    {
        if (nullptr == _Render)
        {
            continue;
        }

        delete _Render;
        _Render = nullptr;
    }

    for (GameEngineCollision* _Collision : CollisionList)
    {
        if (nullptr == _Collision)
        {
            continue;
        }

        delete _Collision;
        _Collision = nullptr;
    }

}

GameEngineLevel* GameEngineActor::GetLevel()
{
    return GetOwner<GameEngineLevel>();
}


GameEngineRender* GameEngineActor::CreateRender(const std::string_view& _Image, int _Order /*= 0*/)
{
    GameEngineRender* Render = CreateRender(_Order);
    Render->SetImage(_Image);
    return Render;
}

GameEngineRender* GameEngineActor::CreateRender(int _Order /*= 0*/)
{
    GameEngineRender* Render = new GameEngineRender();
    // 분명뭔가 좀 보기 좋지 않다.
    Render->SetOwner(this);
    Render->SetOrder(_Order);
    RenderList.push_back(Render);
    return Render;
}

GameEngineCollision* GameEngineActor::CreateCollision(int _GroupIndex)
{
    GameEngineCollision* Collision = new GameEngineCollision();
    // 분명뭔가 좀 보기 좋지 않다.
    Collision->SetOwner(this);
    Collision->SetOrder(_GroupIndex);
    CollisionList.push_back(Collision);
    return Collision;
}

void GameEngineActor::Release()
{
    {
        std::list<GameEngineRender*>::iterator StartIter = RenderList.begin();
        std::list<GameEngineRender*>::iterator EndIter = RenderList.end();

        for (; StartIter != EndIter; )
        {
            GameEngineRender* ReleaseRender = *StartIter;

            if (nullptr == ReleaseRender)
            {
                MsgAssert("nullptr 인 랜더가 내부에 들어있습니다.");
            }

            if (false == ReleaseRender->IsDeath())
            {
                ++StartIter;
                continue;
            }

            StartIter = RenderList.erase(StartIter);

            delete ReleaseRender;
            ReleaseRender = nullptr;
        }
    }
    {
        std::list<GameEngineCollision*>::iterator StartIter = CollisionList.begin();
        std::list<GameEngineCollision*>::iterator EndIter = CollisionList.end();

        for (; StartIter != EndIter; )
        {
            GameEngineCollision* ReleaseCollision = *StartIter;

            if (nullptr == ReleaseCollision)
            {
                MsgAssert("nullptr 인 랜더가 내부에 들어있습니다.");
            }

            if (false == ReleaseCollision->IsDeath())
            {
                ++StartIter;
                continue;
            }

            StartIter = CollisionList.erase(StartIter);

            delete ReleaseCollision;
            ReleaseCollision = nullptr;
        }
    }
}