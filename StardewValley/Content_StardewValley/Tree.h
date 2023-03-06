#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;
class GameEngineCollision;
class Tree : public GameEngineActor
{

public:

	Tree();
	~Tree();

    void RenderOrderUpdate();
    void TreeHpUpdate();

	Tree(const Tree& _Other) = delete;
	Tree(Tree&& _Other) noexcept = delete;
	Tree& operator=(const Tree& _Other) = delete;
	Tree& operator=(Tree&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:
    GameEngineRender* TreeRender = nullptr;
    GameEngineRender* TreeUnderRender = nullptr;

    GameEngineCollision* TreeCollision = nullptr;
    GameEngineCollision* TreeUnderCollision = nullptr;

    bool isHit = false;
    int Hp = 5;
};

