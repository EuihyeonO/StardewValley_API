#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;
class SelectedLine : public GameEngineActor
{

public:

    static void LineOff();
    static void LineOn();
    static void SetLinePos(float4 _pos);
    static bool IsLineOn();

	SelectedLine();
	~SelectedLine();

	SelectedLine(const SelectedLine& _Other) = delete;
	SelectedLine(SelectedLine&& _Other) noexcept = delete;
	SelectedLine& operator=(const SelectedLine& _Other) = delete;
	SelectedLine& operator=(SelectedLine&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:

    static GameEngineRender* SelectedLineRender;
};

