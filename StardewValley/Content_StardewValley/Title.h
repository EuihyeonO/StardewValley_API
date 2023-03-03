#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Button;
class Title : public GameEngineActor
{

public:

    static Title* GetGlobalTitle()
    {
        return globalTitle;
    }

    void CloudReSet();
    void SetObjectAlpha(float _DeltaTime);
    void ObjectMove(float _DeltaTime);
    
    void TimeCount();

    void MoveMountain(float _DeltaTime);

    void ObjectInit();
    void ButtonInit();

    void FadeOut(float _DeltaTime);
    void SetIsClicked();
    void ChangeLevelToHouse();

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
    static Title* globalTitle;

    float mytime = 0;
    float PrevTime = 0;
    float CurTime = 0;
    
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
    GameEngineRender* Cloud2 = nullptr;
    GameEngineRender* Cloud3 = nullptr;
    GameEngineRender* Cloud4 = nullptr;
    GameEngineRender* Cloud5 = nullptr;

    GameEngineRender* Tree = nullptr;

    GameEngineRender* Bird1 = nullptr;
    GameEngineRender* Bird2 = nullptr;


    GameEngineRender* BlackImage = nullptr;

    Button* NewGame = nullptr;
    Button* ExitGame = nullptr;

    float Alpha = 0;
    float Accel1 = 0;
    float Accel2 = 0;
    float Accel3 = 0;

    bool isClicked = false;
    float BlackAlpha = 0;

};

