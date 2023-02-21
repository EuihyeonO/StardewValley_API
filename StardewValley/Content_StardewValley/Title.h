#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Button;
class Title : public GameEngineActor
{

public:

    void ObjectInit();
    void ButtonInit();

    Title();
    ~Title();
    Title(const Title& _Other) = delete;
    Title(Title&& _Other) noexcept = delete;
    Title& operator=(const Title& _Other) = delete;
    Title& operator=(Title&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;

private:
    float mytime = 0;
    int isSet = 0;
    float isCameraSet = 0;

    float4 Mountain2Pos = {350, 440};
    float4 Mountain1Pos = {480, 490};
    float4 TreePos = {0, 490};

    float4 IntroScale = { 0,0 };

    GameEngineRender* intro1 = nullptr;
    GameEngineRender* TitleName = nullptr; 
    GameEngineRender* TitleMountain1 = nullptr;
    GameEngineRender* TitleMountain2 = nullptr;

    GameEngineRender* Cloud1 = nullptr;

    GameEngineRender* Tree = nullptr;

    GameEngineRender* Bird1 = nullptr;
    GameEngineRender* Bird2 = nullptr;

    Button* NewGame = nullptr;
    Button* ExitGame = nullptr;

    int Alpha = 0;
    float Accel1 = 0;
    float Accel2 = 0;
    float Accel3 = 0;

};

