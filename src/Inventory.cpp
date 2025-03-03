#include "Inventory.hpp"
#include "Item.hpp"
#include "enums/Tile.hpp"

Inventory::Inventory()
{
    items.push_back(new Item("Pickaxe"));
    items.push_back(new Item("Dirt", Tile::Dirt));
    items.push_back(new Item("Grass", Tile::Grass));
    items.push_back(new Item("Water", Tile::Water));
}

// Returns true if item added or false if inventory is full
bool Inventory::addItem(Item *newItem)
{
    for (int i = 0; i < sizeof(items); i++)
    {
        if (items[i] == nullptr)
        {
            items[i] = newItem;
            return true;
        }
    }

    return false;
}

void Inventory::removeItem()
{
}

void Inventory::dropItem()
{
}