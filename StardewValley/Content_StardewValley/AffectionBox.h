#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;
class AffectionBox : public GameEngineActor
{

public:

    static void SetGlobalAffectionBox(AffectionBox* _Box)
    {
        globalAffectionBox = _Box;
    }
    static AffectionBox* GetGlobalAffectionBox()
    {
        return globalAffectionBox;
    }
    GameEngineRender* GetAffectionBoxRender()
    {
        return AffectionBoxRender;
    }

    void AffectionBoxOn();
    void AffectionBoxOff();

	AffectionBox();
	~AffectionBox();

	AffectionBox(const AffectionBox& _Other) = delete;
	AffectionBox(AffectionBox&& _Other) noexcept = delete;
	AffectionBox& operator=(const AffectionBox& _Other) = delete;
	AffectionBox& operator=(AffectionBox&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:
    GameEngineRender* AffectionBoxRender = nullptr;

    GameEngineRender* HaleyHeart = nullptr;
    GameEngineRender* SamHeart = nullptr;
    GameEngineRender* PennyHeart = nullptr;
    GameEngineRender* LewisHeart = nullptr;

    static AffectionBox* globalAffectionBox;
};
