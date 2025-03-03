#pragma once
#include <map>
#include "Component.hpp"
#include "Item.hpp"

class Inventory : public Component
{
public:
    Inventory();

    Item *getItem() const { return activeItem < items.size() ? items[activeItem] : nullptr; }
    bool addItem(Item *newItem);
    void removeItem();
    void dropItem();

    std::vector<Item *> getItems() const { return items; }

    int activeItem = 0;

private:
    std::vector<Item *> items;
};