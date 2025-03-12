#pragma once
#include "Game.hpp"
#include "GameObject.hpp"
#include "geometry/Vector.hpp"

class GameObject;
class Transform;
class Collider;
struct BoundingBox;

class PhysicsManager
{
public:
    PhysicsManager(Game *game, int gravity, int maxFallSpeed, int airResistance, int groundResistance) : game(game), gravity(gravity), maxFallSpeed(maxFallSpeed), airResistance(airResistance), groundResistance(groundResistance) {};

    void handleCollisions(GameObject *gameObject);
    void resolveCollisions(Transform *transform, Collider *collider, BoundingBox other);
    bool raycast(Vector origin, Vector direction, int length);

    int gravity;
    int maxFallSpeed;
    int airResistance;
    int groundResistance;

private:
    Game *game;
};