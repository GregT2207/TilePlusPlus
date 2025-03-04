#pragma once
#include <map>
#include "Component.hpp"
#include "Item.hpp"
#include "ResourceManager.hpp"

class Inventory : public Component
{
public:
    Inventory(ResourceManager *resourceManager);

    Item *getItem() const { return activeItem < items.size() ? items[activeItem] : nullptr; }
    bool addItem(Item *newItem);
    void removeItem();
    void dropItem();

    std::vector<Item *> getItems() const { return items; }

    int activeItem = 0;

private:
    ResourceManager *resourceManager;
    std::vector<Item *> items;
};