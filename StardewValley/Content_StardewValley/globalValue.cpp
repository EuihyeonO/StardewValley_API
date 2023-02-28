#include "globalValue.h"
#include "Level_Farm.h"
#include "Level_House.h"
#include "Level_Road.h"
#include "Level_Mine.h"
#include "UI.h"
#include "ContentsEnum.h"
#include "Pierre.h"

#include <GameEnginePlatform/GameEngineInput.h>

float4 globalValue::cameraLimitPos = {0,0};
std::string_view globalValue::CurLevelName;
int globalValue::money = 200;
int globalValue::TotalRevenue = 0;
int globalValue::Day = 1;

globalValue::globalValue()
{
}

globalValue::~globalValue()
{

}


int globalValue::GetKeyInput()
{
    {
        if (Pierre::IsOpenShop() == true)
        {
            return Act::Idle;
        }

        else
        {
            if (true == GameEngineInput::IsDown("MouseInteract"))
            {
                return Act::MouseInteract;
            }

            if (true == GameEngineInput::IsDown("KeyInteract"))
            {
                return Act::KeyInteract;
            }

            else if (true == GameEngineInput::IsPress("LMove") ||
                true == GameEngineInput::IsPress("RMove") ||
                true == GameEngineInput::IsPress("UMove") ||
                true == GameEngineInput::IsPress("DMove"))
            {
                return Act::Move;
            }

            else
            {
                return Act::Idle;
            }
        }
    }
}
