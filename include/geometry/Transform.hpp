#pragma once
#include "components/Component.hpp"
#include "geometry/Vector.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "PhysicsManager.hpp"

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

    void setDirection(Vector newDirection) { direction = newDirection.sgned(); };
    void flipDirectionX() { direction.x = -direction.x; }
    void flipDirectionY() { direction.y = -direction.y; }

    Vector getPosition() const { return position; }
    Vector getVelocity() const { return velocity; }
    Vector getSize() const { return size; }
    Vector getDirection() const { return direction; }

    void update(float deltaTime) override;

private:
    Vector position;
    Vector velocity;
    Vector size;
    Vector direction = {1.0f, 1.0f};

    void applyGravity(float deltaTime);
    void applyDrag(float deltaTime);
};