#pragma once

#include <string_view>
#include <vector>

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineResources.h>


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

    void InitPlayer();
    void InitTool();
    void SetDir();

    void CreateAllAnimation();
    void CreateToolAnimation();
    void CreatePlayerKey();
    void CreatePlayerAnimation(std::string_view State, std::vector<int> _FrameIndex, std::vector<float> _Frametime, int Dir = 0);
   
    void ChangePlayerAnimation(std::string_view _Act);

    bool isPlayerAnimationEnd()
    {
        return PlayerRender->IsAnimationEnd();
    }

    int GetPlayerAnimationFrame()
    {
        return PlayerRender->GetFrame();
    }

    std::string GetDir()
    {
        return Dir;
    }
    const float4 GetDirPos();

    bool isCollisionCrops();
    bool isInteract();
    bool isFront(float4 _pos);

    static void SetIsCollision(bool _isCollision)
    {
        MyPlayer->isCollision = _isCollision;
    }
    static bool GetIsCollision()
    {
        return MyPlayer->isCollision;
    }

    static void SetMyPlayer(Player* _player)
    {
        MyPlayer = _player;
    }
    static void ChangePlayerIdle();

    static bool IsSameCurTool(std::string _ToolName);

    int GetKeyInput();

    void Move(float _DeltaTime);
    void Idle();
    void Interact();
    void OpenInventory();

    void SetIsHarvesting()
    {
        isHarvesting = true;
    }

    void InteractToCrops();
    void InteractToTile();
    const float4 GetInteractPos();
    void InteractToNPC();

    void test();

    void ToolChange();
    void ToolPosUpdate();
    float4 SetToolPos();

    void Harvesting();

    void ActingUpdate(float _DeltaTime);
    void CurToolTypeUpdate();
protected:

    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;

private:
    float MoveSpeed = 300.0f;
    int CurToolType = -1;
 
    GameEngineRender* PlayerRender = nullptr;
    GameEngineRender* CurTool = nullptr;

    GameEngineCollision* ColBody = nullptr;
    GameEngineCollision* ColFullBody = nullptr;

    GameEngineRender* Pick = nullptr;
    GameEngineRender* Axe = nullptr;
    GameEngineRender* Hoe = nullptr;
    GameEngineRender* Watering = nullptr;
    GameEngineRender* Default = nullptr;

    GameEngineImage* ColMap = nullptr;

    GameEngineCollision* ColTool = nullptr;

    GameEngineSoundPlayer WalkSound;

    std::map<std::string, GameEngineRender*> Tool;


    bool isDebug = false;
    bool isCollision = false;
    bool isHarvesting = false;

    static Player* MyPlayer;

    std::string Dir = "D";
    int inputNumberKey = -1;
};

