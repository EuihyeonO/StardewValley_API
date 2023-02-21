#include <string>
#include <vector>

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTileMap.h>

#include "Level_Farm.h"
#include "Farm.h"
#include "Player.h"
#include "UI.h"
#include "Inventory.h"
#include "Item.h"
#include "ContentsEnum.h"
#include "Crops.h"
#include "globalValue.h"


void Level_Farm::InitTile()
{
    TileMap->CreateTileMap(2560 / 64, 1024 / 64, 10, 0, float4{ 64, 64 });
    TileMap->CreateTileMapCollision(2560 / 64, 1024 / 64, 5, static_cast<int>(ActorType::Tile), float4{ 64, 64 });
    TileMap->SetFloorSetting(0, "HoeDirt.bmp");

    TileMap->SetFloorSetting(SeedName::Parsnip, "Parsnip.bmp");
    TileMap->SetFloorSetting(SeedName::Cauliflower, "Cauliflower.bmp");
    TileMap->SetFloorSetting(SeedName::Garlic , "Garlic.bmp");
    TileMap->SetFloorSetting(SeedName::Bean , "Bean.bmp");

}

int Level_Farm::CheckUpdateTile(float4 _pos)
{
    for (int i = 1; i < 5; i++)
    {
        if (TileMap->GetTile(i, _pos)->IsUpdate() == true)
        {
            return i;
        }
    }
    return -1;
}

int Level_Farm::GetLastIndexCrops(int _SeedType)
{
    if (_SeedType == SeedName::Parsnip)
    {
        return 5;
    }
    else if (_SeedType == SeedName::Cauliflower)
    {
        return 6;
    }
    else if (_SeedType == SeedName::Garlic)
    {
        return 4;
    }
    else if (_SeedType == SeedName::Bean)
    {
        return 7;
    }
    else 
    {
        return -1;
    }
}

bool Level_Farm::IsMaxGrow(float4 _pos, int _SeedType)
{
    if (TileMap->GetTile(_SeedType, _pos)->GetFrame() >= GetLastIndexCrops(_SeedType))
    {
        return true;
    }

    if (TileMap->GetTile(_SeedType, _pos)->GetFrame() < GetLastIndexCrops(_SeedType))
    {
        return false;
    }

    else
    {
        return false;
    }
}

void Level_Farm::SetSeedPos(float4 _pos, int _SeedType)
{
    if (_SeedType == SeedName::Parsnip)
    {
        TileMap->GetTile(_SeedType, _pos)->SetMove({ 0, -16 });
    }
    else if (_SeedType == SeedName::Garlic || _SeedType == SeedName::Bean)
    {
        TileMap->GetTile(_SeedType, _pos)->SetMove({ 0, -24 });
    }
}