#pragma once
#include "enums/Tile.hpp"

class Item
{
public:
    Item(std::string name, std::optional<Tile> tile = std::nullopt) : name(name), tile(tile) {};

    std::string name;
    std::optional<Tile> tile;
};