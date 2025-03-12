#pragma once

class PhysicsManager
{
public:
    PhysicsManager(int gravity, int maxFallSpeed, int airResistance, int groundResistance) : gravity(gravity), maxFallSpeed(maxFallSpeed), airResistance(airResistance), groundResistance(groundResistance) {};

    int gravity;
    int maxFallSpeed;
    int airResistance;
    int groundResistance;
};