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
    Portal,
};
