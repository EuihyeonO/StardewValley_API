#pragma once

#include <string_view>
#include <vector>

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineResources.h>


class Mummy;
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
    static void ChangePlayerIdle(const std::string& _Dir);

    static bool IsSameCurTool(std::string _ToolName);
    static void SetPlayerAlpha(int _Alpha);
 
    int GetKeyInput();
    void GetItem(const std::string_view& _itemName);
    void Move(float _DeltaTime);
    void Idle();
    void Interact();
    void OpenMenu();

    void HammerCollisionUpdate();

    void SetIsHarvesting()
    {
        isHarvesting = true;
    }

    bool GetisHarvesting()
    {
        return isHarvesting;
    }

    void PlayerStop()
    {
        isAbleAct = false;
    }

    void PlayerStopOff()
    {
        isAbleAct = true;
    }

    static bool GetIsAbleAct()
    {
        return MyPlayer->isAbleAct;
    }

    static int GetToolFrame();

    void InteractToTile();
    const float4 GetInteractPos();
    void InteractToNPC();
    void isCollidedToNPC();
    
    void HitByMonster(float _DeltaTime);
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
    float MoveSpeed = 250.0f;
    int CurToolType = -1;
 
    GameEngineRender* PlayerRender = nullptr;
    GameEngineRender* Shadow = nullptr;
    GameEngineRender* CurTool = nullptr;

    GameEngineCollision* ColBody = nullptr;
    GameEngineCollision* ColFullBody = nullptr;
    GameEngineCollision* ColInteract = nullptr;


    GameEngineRender* Pick = nullptr;
    GameEngineRender* Axe = nullptr;
    GameEngineRender* Hoe = nullptr;
    GameEngineRender* Watering = nullptr;
    GameEngineRender* Hammer = nullptr;
    GameEngineRender* Default = nullptr;

    GameEngineImage* ColMap = nullptr;

    GameEngineCollision* ColTool = nullptr;
    GameEngineCollision* HammerCollision = nullptr;

    std::map<std::string, GameEngineRender*> Tool;
    std::vector<Mummy*> CopyList;

    float4 BouncePos = { 0,0 };
    float Accel = 10;
    float PrevTime = 0;
    float CurTime = 0;
    float mytime = 0;

    bool isDebug = false;
    bool isCollision = false;
    bool isHarvesting = false;
    bool isHit = false;
    bool isAbleAct = true;
    bool timeCheckStart = false;

    static Player* MyPlayer;

    std::string Dir = "D";
    int inputNumberKey = -1;

    bool isColToNPC = false;

    GameEngineRender* GetItemRender = nullptr;
};

