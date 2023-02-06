#pragma once

#include <string_view>
#include <vector>

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

class Inventory;
class Player : public GameEngineActor
{

public:

	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete; 

    static Player* GetPlayer()
    {
        return MyPlayer;
    }
    void Render(float _Time) override;

    void InitPlayer();
    void InitTool();
    void SetDir();

    void CreateAllAnimation();
    void CreatePlayerKey();
    void CreatePlayerAnimation(std::string_view State, std::vector<int> _FrameIndex, std::vector<float> _Frametime, int Dir = 0);
    void ChangePlayerAnimation(std::string_view _Act);

    bool isInteract();
    int GetKeyInput();

    void Move(float _DeltaTime);
    void Idle();
    void Interact(float _DeltaTime);

    void ToolChange();
    static bool IsSameCurTool(std::string _ToolName);

    void ActingUpdate(float _DeltaTime);

protected:

    void Start() override;
    void Update(float _DeltaTime) override;

private:
    float MoveSpeed = 200.0f;

    GameEngineRender* PlayerRender = nullptr;
    GameEngineRender* CurTool = nullptr;

    GameEngineRender* Pick = nullptr;
    GameEngineRender* Axe = nullptr;
    GameEngineRender* Hoe = nullptr;

    GameEngineCollision* ColPick = nullptr;
    GameEngineCollision* ColAxe = nullptr;
    GameEngineCollision* ColHoe = nullptr;

    std::map<std::string, GameEngineRender*> Tool;

    static Player* MyPlayer;

    std::string Dir = "D";


};

