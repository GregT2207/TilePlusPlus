#pragma once
#include "Component.hpp"
#include "Vector.hpp"

class GameObject;

class Transform : public Component
{
public:
    Transform(GameObject *owner);

    void setPosition(float x, float y) { position = {x, y}; };
    void setPosition(Vector newPos) { position = newPos; };
    void addPosition(float x, float y) { position += {x, y}; };
    void addPosition(Vector newPos) { position += newPos; };

    void setX(float x) { position.x = x; };
    void setY(float y) { position.y = y; };

    Vector getPosition() const { return position; }

    void update(float deltaTime);

private:
    Vector position;
};