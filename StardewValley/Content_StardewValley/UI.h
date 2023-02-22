#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class Inventory;
class UI : public GameEngineActor
{
    friend Inventory;

public:


	UI();
	~UI();

    static UI* GetUI()
    {
        return GlobalUI;
    }

    void UI_ONOFF();
    void RenderMoney(int _Money);

	UI(const UI& _Other) = delete;
	UI(UI&& _Other) noexcept = delete;
	UI& operator=(const UI& _Other) = delete;
	UI& operator=(UI&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;

private:
    static UI* GlobalUI;

    float4 CameraPos = { 0,0 };
    float4 Screensize = { 0 ,0 };
    GameEngineRender* TimeBar = nullptr;
    GameEngineRender* StatusBar = nullptr;

    NumberRenderObject MoneyRender;

    std::string time;

    int StartTime = 0;
    int EndTime = 0;

    int GlobalTime = 0;
};

