#pragma once
#include <string>

#include "Item.h"
#include "crops.h"
#include "Inventory.h"



/*
* 대상(나무, 돌, 농작물 등)이 도구와 충돌할 때마다 life가 1씩 감소하며, life가 0이되면 기존 render이 off하고
* 새로운 render이 On된다. (바닥에 드랍된 아이템)
* 새로 render된 아이템과 Player가 충돌하게 되면, CreateItem 함수가 호출되며, 아이템이 인벤토리에 들어가게되는 구조
* 로 만들 계획..
* 
* 이었으나 동적할당을 빼고, level단계에서 아이템 actor를 만드는 쪽으로 가야할 듯
*/


