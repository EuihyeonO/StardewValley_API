#include <string>
#include <vector>

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
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
    
    ValidCollisionTileOn();

    ColllidedTile;

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
    float4 TilePos = TileMap->GetTile(0, _pos)->GetPosition();
    float4 SeedPos = TileMap->GetTile(_SeedType, _pos)->GetPosition();

    if (_SeedType == SeedName::Parsnip)
    {
        if(TilePos.y - SeedPos.y != 16)
        {
            TileMap->GetTile(_SeedType, _pos)->SetMove({ 0, -16 });
        }
    }
    else if (_SeedType == SeedName::Garlic || _SeedType == SeedName::Bean)
    {
        if (TilePos.y - SeedPos.y != 24)
        {
            TileMap->GetTile(_SeedType, _pos)->SetMove({ 0, -24 });
        }
    }
}

void Level_Farm::isCollisionToPlayer()
{
    for (int i = 0; i < ColllidedTile.size(); i++)
    { 
        if (true == ColllidedTile[i]->Collision({ .TargetGroup = static_cast<int>(ActorType::Player) , .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
        {
            float4 Pos = ColllidedTile[i]->GetPosition();
            int Zindex = CheckUpdateTile(Pos);

            if (Zindex != -1) 
            {
                ColllidedTileRender.push_back(TileMap->GetTile(Zindex, Pos));
                ColllidedTileRender[ColllidedTileRender.size()-1]->SetAlpha(100);
            }
        }
    }
    
}

void Level_Farm::SetTileAlphaMax()
{
    for (int i = 0; i < ColllidedTileRender.size(); i++)
    {
        ColllidedTileRender[i]->SetAlpha(255);
    }
}

void Level_Farm::ValidCollisionTileOn()
{
    GameEngineImage* ColMap = ColMap = GameEngineResources::GetInst().ImageFind("FarmC.bmp");
    
    float X = 0;
    float Y = 0;
    for (X = 0; X < 2560;)
    {
        for (Y = 0; Y < 1024;)
        {
            if (ColMap->GetPixelColor(float4(X, Y), RGB(255, 0, 255)) == RGB(255, 0, 255))
            {
                TileMap->GetTileCollision(0, float4(X, Y))->On();
                ColllidedTile.push_back(TileMap->GetTileCollision(0, float4(X, Y)));
            }
            Y += 64;
        }    
        X += 64;
    }
}

void Level_Farm::Grow_Up()
{
    size_t Size = OnTileList.size();

    for (int i = 0; i < Size; i++)
    {
        float4 TilePos = OnTileList[i]->GetPosition();
        int SeedName = CheckUpdateTile(TilePos);

        if (TileMap->GetTile(0, TilePos)->GetFrame() == 1)
        {
            TileMap->SetTileFrame(0, TilePos, 0);

            int frame = OnTileList[i]->GetFrame();

            if (frame >= GetLastIndexCrops(SeedName))
            {
                return;
            }
            OnTileList[i]->SetFrame(frame + 1);
        }
    }
}

void Level_Farm::DeleteTileToList(int _SeedName, float4 _pos)
{
    size_t Size = OnTileList.size();

    for(int i = 0; i < Size; i++)
    {
        if (OnTileList[i] == TileMap->GetTile(_SeedName, _pos))
        {
            OnTileList[i]->Off();
            OnTileList.erase(OnTileList.begin() + i);
        }
    }
}