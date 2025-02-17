#pragma once
#include "Component.hpp"
#include "Vector.hpp"

class GameObject;

class Transform : public Component
{
public:
    Transform(Vector position = {0.0f, 0.0f}, Vector velocity = {0.0f, 0.0f}, Vector size = {10.0f, 10.0f});

    void setPosition(Vector newPos) { position = newPos; };
    void addPosition(Vector newPos) { position += newPos; };
    void setX(float x) { position.x = x; };
    void setY(float y) { position.y = y; };
    void addX(float x) { position.x += x; };
    void addY(float y) { position.y += y; };

    void setVelocity(Vector newVel) { velocity = newVel; };
    void setVelocityX(float x) { velocity.x = x; };
    void setVelocityY(float y) { velocity.y = y; };
    void addVelocity(Vector newVel) { velocity += newVel; };
    void addVelocityX(float x) { velocity.x += x; };
    void addVelocityY(float y) { velocity.y += y; };

    void setSize(Vector newSize) { size = newSize; };
    void setWidth(float x) { size.x = x; };
    void setHeight(float y) { size.y = y; };

    Vector getPosition() const { return position; }
    Vector getVelocity() const { return velocity; }
    Vector getSize() const { return size; }

    void update(float deltaTime, int gravity, int worldHeight) override;

protected:
    Vector position;
    Vector velocity;
    Vector size;

private:
    void applyGravity(float deltaTime, int gravity, int worldHeight);
};