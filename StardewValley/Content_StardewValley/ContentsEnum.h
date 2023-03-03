 #pragma once

enum Act
{
    Left = 1,
    Right,
    Idle,
    Move,
    MouseInteract,
    Menu,
    ChangeQuickSlot,
    ChangeQuickSlotItem,
    KeyInteract,
};

enum class ActorType
{
    Player = 10,
    FullPlayer,
    PlayerInteract,
    Crops,
    Tool,
    Portal,
    NPC,
    Mouse,
    Tile,
    Item,
    Bed,
    Stone,
    OrderChange,
};

enum class ItemType
{
    Crops,
    Pick,
    Hoe,
    Watering,
    Axe,
    Hammer,
    Seed,
    Mineral,
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
    Cauliflower,
    Garlic,
    Bean,
};


enum class MineralName
{
    Stone,
    Topaz,
};