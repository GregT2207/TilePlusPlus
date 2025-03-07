#pragma once
#include "enums/Tile.hpp"

class Item
{
public:
    Item(string name, SDL_Texture *texture, optional<Tile> tile = nullopt) : name(name), texture(texture), tile(tile) {};

    SDL_Texture *getTexture() const { return texture; }
    optional<Tile> getTile() const { return tile; }

    string name;

private:
    SDL_Texture *texture;
    optional<Tile> tile;
};