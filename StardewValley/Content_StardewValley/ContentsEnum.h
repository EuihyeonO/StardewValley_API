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
    //����
    Tool,
    //����
    Seed,
    //��� �� ä���� ��Ȯ�� ��
    Crops1,
    //��Ÿ��� ��������, �� ��
    Etc
};
