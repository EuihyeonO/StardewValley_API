#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <string>

class GameEngineRender;
class GameEngineCollision;
class Obstacle : public GameEngineActor
{

public:

    void NoticeTextBoxOn(float _DeltaTime);
    void NoticeTextBoxOff();
    void NoticeTextOn();
    void NoticeTextOff();
    void KeyInteractUpdate();
	Obstacle();
	~Obstacle();

	Obstacle(const Obstacle& _Other) = delete;
	Obstacle(Obstacle&& _Other) noexcept = delete;
	Obstacle& operator=(const Obstacle& _Other) = delete;
	Obstacle& operator=(Obstacle&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:
    GameEngineRender* Obstacle1 = nullptr;
    GameEngineRender* Obstacle2 = nullptr;
    GameEngineRender* Obstacle3 = nullptr;

    GameEngineCollision* ObstacleCollision1 = nullptr;
    GameEngineCollision* ObstacleCollision2 = nullptr;
    GameEngineCollision* ObstacleCollision3 = nullptr;

    GameEngineRender* noticeTextBox = nullptr;
    GameEngineRender* noticeTextShadow = nullptr;

    GameEngineRender* noticeText = nullptr;

    float4 TextScale = { 0,0 };

    bool isKeyInteract = false;
    bool isSetText = false;

    std::string noticeTextString = "";
    std::string CopyText = " ";

    float PrevTime = 0;
    float CurTime = 0;
    float CountTime = 0;
    float CountSoundTime = 0;

    int StringIndex = 0;
};

