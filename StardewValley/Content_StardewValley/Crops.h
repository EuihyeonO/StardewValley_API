#pragma once

#include <string_view>
#include <vector>

#include <GameEngineCore/GameEngineActor.h>


class Item;
class Crops : public GameEngineActor
{

public:

	Crops();
	~Crops();

    void InitCrop(std::string _Name, float4 _Pos);
    GameEngineCollision* GetCollisionImage()
    {
        return CollisionImage;
    }

	Crops(const Crops& _Other) = delete;
	Crops(Crops&& _Other) noexcept = delete;
	Crops& operator=(const Crops& _Other) = delete;
	Crops& operator=(Crops&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;

private:
    int life = 0;

    std::string CropName;
    GameEngineRender* Image = nullptr;
    GameEngineCollision* CollisionImage = nullptr;
};

