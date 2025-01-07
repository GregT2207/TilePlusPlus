#include "Transform.hpp"

Transform::Transform(GameObject *owner) : Component(owner), position({0.0f, 0.0f}) {};

void Transform::update(float deltaTime)
{
    // do stuff
}