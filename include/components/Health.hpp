#pragma once
#include "components/Component.hpp"
#include "GameObject.hpp"
#include "geometry/Vector.hpp"

class Health : public Component
{
public:
    Health(int maxHp = 100, int initialHp = 0) : hp(initialHp > 0 ? initialHp : maxHp), maxHp(maxHp)
    {
        visibleHp = hp;
    }

    void render(SDL_Renderer *renderer) override;
    int hurt(int amount);
    int hurtKnockback(int hurtAmount, int knockbackAmount, Vector overlap);
    int heal(int amount);
    void die();

    int getHp() const { return hp; }
    int getMaxHp() const { return maxHp; }
    int getVisibleHp() const { return visibleHp; }

private:
    int hp;
    int maxHp;
    int visibleHp; // Used for lerp in healthbar rendering
};