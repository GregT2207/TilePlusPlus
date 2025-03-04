#include "Inventory.hpp"
#include "GameObject.hpp"
#include "Item.hpp"
#include "enums/Tile.hpp"

Inventory::Inventory(ResourceManager *resourceManager) : resourceManager(resourceManager)
{
    items.push_back(new Item("Midnight Slasher", resourceManager->loadTexture("sprites/sword.png")));
    items.push_back(new Item("Cradle Picker", resourceManager->loadTexture("sprites/pickaxe.jpg")));
    items.push_back(new Item("Dirt", resourceManager->loadTexture("sprites/dirt.jpg"), Tile::Dirt));
    items.push_back(new Item("Grass", resourceManager->loadTexture("sprites/grass.jpg"), Tile::Grass));
    items.push_back(new Item("Water", resourceManager->loadTexture("sprites/water.jpg"), Tile::Water));
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