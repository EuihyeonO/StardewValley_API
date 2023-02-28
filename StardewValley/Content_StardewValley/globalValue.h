#pragma once
#include "Item.h"
#include "Inventory.h"
#include <GameEngineBase/GameEngineMath.h>

#include <vector>
#include <string>
#include <string_view>

class UI;
class globalValue
{

public:

    static float4 GetcameraLimitPos()
    {
        return cameraLimitPos;
    }

    static void SetcameraLimitPos(float4 _pos)
    {
        cameraLimitPos = _pos;
    }


    static int GetKeyInput();


    static void SetMoney(int Num)
    {
        money = Num;
    }

    static void PlusToMoney(int Num)
    {
        money += Num;
    }

    static void DayPlus()
    {
        ++Day;
    }
    static int GetMoney()
    {
        return money;
    }

    static int GetDay()
    {
        return Day;
    }

    static void SetCurLevelName(std::string_view _name)
    {
        CurLevelName = _name;
    }

    static int GetTotalRevenue()
    {
        return TotalRevenue;
    }

    static void PlusToTotalRevenue(int _money)
    {
        TotalRevenue += _money;
    }



    globalValue();
	~globalValue();

    globalValue(const globalValue& _Other) = delete;
    globalValue(globalValue&& _Other) noexcept = delete;
    globalValue& operator=(const globalValue& _Other) = delete;
    globalValue& operator=(globalValue&& _Other) noexcept = delete;

protected:

private:

    static float4 cameraLimitPos;
    static std::string_view CurLevelName;

    static int money;
    static int TotalRevenue;
    static int Day;
};
