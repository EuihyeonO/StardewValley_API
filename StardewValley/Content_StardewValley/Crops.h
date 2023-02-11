#pragma once

#include <string_view>
#include <vector>

#include <GameEngineCore/GameEngineActor.h>


class Item;
class GameEngineCollision;
class Crops : public GameEngineActor
{

public:

	Crops();
	~Crops();

    void SetCrops();
    void SetName(std::string _Name);

    GameEngineCollision* GetCollisionImage()
    {
        return CollisionImage;
    }


    int GetLife()
    {
        return life;
    }
    bool isSet()
    {
        return isSetting;
    }
    std::string GetName()
    {
        return CropName + "T.BMP";
    }

    void SetCrops(std::string _Name);
    void GrowUp();

    void CollisionOn();
    void CollisionOff();
    bool IsCollisionUpdate();

	Crops(const Crops& _Other) = delete;
	Crops(Crops&& _Other) noexcept = delete;
	Crops& operator=(const Crops& _Other) = delete;
	Crops& operator=(Crops&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;

private:
    int life = 5;
    bool isSetting = false;

    std::string CropName = "0";

    GameEngineRender* Image = nullptr;
    GameEngineCollision* CollisionImage = nullptr;
};

