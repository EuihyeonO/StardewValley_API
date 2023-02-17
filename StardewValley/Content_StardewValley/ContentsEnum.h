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
    NPC,
};

enum class ItemType
{
    Crops,
    Pick,
    Hoe,
    Watering,
    Axe,
    Seed,
};

enum class RenderOrder
{
    Map,
    Player,
    Tool,
    Tile, 
    Layer,
};


enum SeedName
{
    Parsnip = 1,

};
