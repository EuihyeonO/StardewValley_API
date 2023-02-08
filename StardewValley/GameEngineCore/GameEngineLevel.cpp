#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include "GameEngineCollision.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>

bool GameEngineLevel::IsDebugRender = false;
float4 GameEngineLevel::TextOutStart = float4::Zero;
std::vector<std::string> GameEngineLevel::DebugTexts;

GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
    // 편하게 for문을 돌리게 하기 위해서 17인부터 
    for (std::pair<int, std::list<GameEngineActor*>> UpdateGroup : Actors)
    {
        std::list<GameEngineActor*>& ActorList = UpdateGroup.second;

        for (GameEngineActor* Actor : ActorList)
        {
            // Actors.erase()
            if (nullptr != Actor)
            {
                delete Actor;
                Actor = nullptr;
            }
        }
    }

    Actors.clear();
}

float4 GameEngineLevel::GetMousePos()
{
    return GameEngineWindow::GetMousePosition();
}
float4 GameEngineLevel::GetMousePosToCamera()
{
    return GameEngineWindow::GetMousePosition() + CameraPos;
}

void GameEngineLevel::ActorStart(GameEngineActor* _Actor, int _Order)
{
    if (nullptr == _Actor)
    {
        MsgAssert("nullptr 액터를 Start하려고 했습니다.");
        return;
    }

    _Actor->SetOwner(this);
    _Actor->SetOrder(_Order);
    _Actor->Start();
}

void GameEngineLevel::ActorsUpdate(float _DeltaTime)
{
    {
        std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
        std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

        for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
        {
            std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

            for (GameEngineActor* Actor : ActorList)
            {
                // Actors.erase()
                if (nullptr == Actor || false == Actor->IsUpdate())
                {
                    continue;
                }

                Actor->LiveTime += _DeltaTime;
                Actor->Update(_DeltaTime);
            }
        }
    }

    {
        std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
        std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

        for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
        {
            std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

            for (GameEngineActor* Actor : ActorList)
            {
                // Actors.erase()
                if (nullptr == Actor || false == Actor->IsUpdate())
                {
                    continue;
                }

                Actor->LateUpdate(_DeltaTime);
            }
        }
    }
}

void GameEngineLevel::Release()
{
    { // 콜리전 삭제
        std::map<int, std::list<GameEngineCollision*>>::iterator GroupStartIter = Collisions.begin();
        std::map<int, std::list<GameEngineCollision*>>::iterator GroupEndIter = Collisions.end();

        for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
        {
            std::list<GameEngineCollision*>& CollisionList = GroupStartIter->second;

            std::list<GameEngineCollision*>::iterator CollisionIterStart = CollisionList.begin();
            std::list<GameEngineCollision*>::iterator CollisionIterEnd = CollisionList.end();

            for (; CollisionIterStart != CollisionIterEnd; )
            {
                GameEngineCollision* ReleaseCollision = *CollisionIterStart;

                // Actors.erase()
                if (nullptr != ReleaseCollision && false == ReleaseCollision->IsDeath())
                {
                    ++CollisionIterStart;
                    continue;
                }

                CollisionIterStart = CollisionList.erase(CollisionIterStart);
            }
        }
    }

    { // 랜더러만 삭제
        std::map<int, std::list<GameEngineRender*>>::iterator GroupStartIter = Renders.begin();
        std::map<int, std::list<GameEngineRender*>>::iterator GroupEndIter = Renders.end();

        for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
        {
            std::list<GameEngineRender*>& RenderList = GroupStartIter->second;

            std::list<GameEngineRender*>::iterator RenderIterStart = RenderList.begin();
            std::list<GameEngineRender*>::iterator RenderIterEnd = RenderList.end();

            for (; RenderIterStart != RenderIterEnd; )
            {
                GameEngineRender* ReleaseRender = *RenderIterStart;

                // Actors.erase()
                if (nullptr != ReleaseRender && false == ReleaseRender->IsDeath())
                {
                    ++RenderIterStart;
                    continue;
                }

                RenderIterStart = RenderList.erase(RenderIterStart);
            }
        }
    }

    { // 액터만 삭제

        std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
        std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

        for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
        {
            std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

            std::list<GameEngineActor*>::iterator ActorIterStart = ActorList.begin();
            std::list<GameEngineActor*>::iterator ActorIterEnd = ActorList.end();

            for (; ActorIterStart != ActorIterEnd; )
            {
                GameEngineActor* ReleaseActor = *ActorIterStart;

                // Actors.erase()
                if (nullptr != ReleaseActor && false == ReleaseActor->IsDeath())
                {
                    ReleaseActor->Release();
                    ++ActorIterStart;
                    continue;
                }

                ActorIterStart = ActorList.erase(ActorIterStart);

                delete ReleaseActor;
                ReleaseActor = nullptr;
            }
        }
    }
}

void GameEngineLevel::ActorsRender(float _DeltaTime)
{
    {
        std::map<int, std::list<GameEngineRender*>>::iterator GroupStartIter = Renders.begin();
        std::map<int, std::list<GameEngineRender*>>::iterator GroupEndIter = Renders.end();

        for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
        {
            std::list<GameEngineRender*>& RenderList = GroupStartIter->second;

            for (GameEngineRender* Renderer : RenderList)
            {
                // Actors.erase()
                if (nullptr == Renderer || false == Renderer->IsUpdate())
                {
                    continue;
                }

                Renderer->Render(_DeltaTime);
            }
        }
    }

    {
        std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
        std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

        for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
        {
            std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

            for (GameEngineActor* Actor : ActorList)
            {
                // Actors.erase()
                if (nullptr == Actor || false == Actor->IsUpdate())
                {
                    continue;
                }

                Actor->Render(_DeltaTime);
            }
        }
    }

    // CollisionDebugRender
    { // 콜리전 삭제
        if (true == IsDebugRender)
        {
            std::map<int, std::list<GameEngineCollision*>>::iterator GroupStartIter = Collisions.begin();
            std::map<int, std::list<GameEngineCollision*>>::iterator GroupEndIter = Collisions.end();

            for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
            {
                std::list<GameEngineCollision*>& CollisionList = GroupStartIter->second;
                std::list<GameEngineCollision*>::iterator CollisionIterStart = CollisionList.begin();
                std::list<GameEngineCollision*>::iterator CollisionIterEnd = CollisionList.end();

                for (; CollisionIterStart != CollisionIterEnd; ++CollisionIterStart)
                {
                    GameEngineCollision* DebugCollision = *CollisionIterStart;
                    if (nullptr == DebugCollision || false == DebugCollision->IsUpdate())
                    {
                        continue;
                    }
                    DebugCollision->DebugRender();
                }
            }
        }
    }

    // 여러분들의 text 출력
    {
        TextOutStart = float4::Zero;

        for (size_t i = 0; i < DebugTexts.size(); i++)
        {
            HDC ImageDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
            TextOutA(ImageDc, TextOutStart.ix(), TextOutStart.iy(), DebugTexts[i].c_str(), static_cast<int>(DebugTexts[i].size()));
            TextOutStart.y += 20.0f;
        }

        DebugTexts.clear();
    }
}

void GameEngineLevel::ActorLevelChangeEnd(GameEngineLevel* _NextLevel)
{
    {
        std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
        std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

        for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
        {
            std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

            for (GameEngineActor* Actor : ActorList)
            {
                Actor->LevelChangeEnd(_NextLevel);
            }
        }
    }
}

void GameEngineLevel::ActorLevelChangeStart(GameEngineLevel* _PrevLevel)
{
    {
        std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
        std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

        for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
        {
            std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

            for (GameEngineActor* Actor : ActorList)
            {
                Actor->LevelChangeStart(_PrevLevel);
            }
        }
    }
}

void GameEngineLevel::PushRender(GameEngineRender* _Render, int _ChangeOrder)
{
    // 0 => 10
    Renders[_Render->GetOrder()].remove(_Render);

    _Render->GameEngineObject::SetOrder(_ChangeOrder);

    if (nullptr == _Render)
    {
        MsgAssert("nullptr인 랜더를 랜더링 그룹속에 넣으려고 했습니다.");
    }

    // 먼저 이미 들어가있을수도 있다.
    Renders[_Render->GetOrder()].push_back(_Render);
}

void GameEngineLevel::PushCollision(GameEngineCollision* _Collision)
{
    if (nullptr == _Collision)
    {
        MsgAssert("nullptr인 충돌체를 충돌 그룹속에 넣으려고 했습니다.");
    }

    // 먼저 이미 들어가있을수도 있다.
    Collisions[_Collision->GetOrder()].push_back(_Collision);
}