#pragma once
#include "enums/Tile.hpp"

class Item
{
public:
    Item(std::string name, SDL_Texture *texture, std::optional<Tile> tile = std::nullopt) : name(name), texture(texture), tile(tile) {};

    SDL_Texture *getTexture() const { return texture; }
    std::optional<Tile> getTile() const { return tile; }

    std::string name;

private:
    SDL_Texture *texture;
    std::optional<Tile> tile;
};