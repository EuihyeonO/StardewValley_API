 #pragma once

enum Act
{
    Left = 1,
    Right,
    Idle,
    Move,
    Interact,
    Menu,
    ChangeItem,
};

enum class ActorType
{
    Player,
    Crops,
    Tool,
};

enum class Itemtype
{
    //도구
    Tool,
    //씨앗
    Seed,
    //농사 및 채집물 수확한 것
    Crops1,
    //기타재료 나뭇가지, 돌 등
    Etc
};
