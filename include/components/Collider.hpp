#pragma once
#include <SDL2/SDL.h>
#include "math.h"
#include "components/Component.hpp"
#include "geometry/Vector.hpp"
#include "geometry/BoundingBox.hpp"

class Collider : public Component
{
public:
    Collider(Vector size, Vector offset = Vector{0.0f, 0.0f}, bool isStatic = false);

    void update(float deltaTime) override;
    void followTransform();
    void render(SDL_Renderer *renderer) override;

    BoundingBox getBoundingBox() const;
    Vector getGap(const BoundingBox b);
    Vector getOverlap(const BoundingBox b);

    void setSize(const Vector newSize) { size = newSize; }
    void addSize(const Vector newSize) { size += newSize; }
    void setOffset(const Vector newOffset) { offset = newOffset; }
    void addOffset(const Vector newOffset) { offset += newOffset; }
    void setGrounded(bool newGrounded) { grounded = newGrounded; }

    Vector getPosition() const { return position; }
    Vector getSize() const { return size; };
    Vector getOffset() const { return offset; };
    bool isGrounded() const { return grounded; }

    bool isStatic = false;

protected:
    Vector position;
    Vector size;
    Vector offset;
    SDL_Color debugColor;

private:
    static bool debug;
    bool grounded = false;
};