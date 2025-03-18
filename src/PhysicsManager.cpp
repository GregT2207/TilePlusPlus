#include "PhysicsManager.hpp"
#include "GameObject.hpp"

void PhysicsManager::handleCollisions(GameObject *gameObject)
{
    Transform *transform = gameObject->getComponent<Transform>();
    Collider *collider = gameObject->getComponent<Collider>();

    if (transform && collider && !collider->isStatic)
    {
        collider->setGrounded(false);

        // Handle collisions for game objects
        for (Collider *otherCollider : game->colliders)
        {
            if (collider == otherCollider)
            {
                continue;
            }

            resolveCollisions(transform, collider, otherCollider->getBoundingBox());
        }

        // Handle collisions for tiles
        int tileSize = game->getTileSize();
        Vector tileMapOffset = game->getTileMapOffset();

        BoundingBox boundingBox = collider->getBoundingBox();

        int yRangeStart = ((boundingBox.y - (static_cast<int>(boundingBox.y) % tileSize)) / tileSize) - 2 - tileMapOffset.y;
        int yRangeEnd = ((boundingBox.y + boundingBox.h) - (static_cast<int>(boundingBox.y + boundingBox.h) % tileSize)) / tileSize + 1 - tileMapOffset.y;
        int xRangeStart = ((boundingBox.x - (static_cast<int>(boundingBox.x) % tileSize)) / tileSize) - 2 - tileMapOffset.x;
        int xRangeEnd = ((boundingBox.x + boundingBox.w) - (static_cast<int>(boundingBox.x + boundingBox.w) % tileSize)) / tileSize + 1 - tileMapOffset.x;

        float waterOverlap = 0.0f;

        for (int y = yRangeStart; y < yRangeEnd; y++)
        {
            if (y < 0 || y >= game->tiles.size())
                continue;

            for (int x = xRangeStart; x < xRangeEnd; x++)
            {
                if (x < 0 || x >= game->tiles[y].size())
                    continue;

                if (game->tiles[y][x] == Tile::Air)
                {
                    continue;
                }

                BoundingBox tileBb = {static_cast<int>((x + tileMapOffset.x) * tileSize), static_cast<int>((y + tileMapOffset.y) * tileSize), tileSize, tileSize};

                if (game->tiles[y][x] == Tile::Water)
                {
                    Vector overlap = collider->getOverlap(tileBb);
                    waterOverlap = std::max(waterOverlap, overlap.y);
                    continue;
                }

                resolveCollisions(transform, collider, tileBb);
            }
        }

        if (waterOverlap > 0)
        {
            const float defaultBuoyancy = 2.0f;
            const float bobbingBuoyancy = defaultBuoyancy * 3.0f;

            float waterBuoyancy = 0.0f;
            if ((waterOverlap > tileSize * 0.1f) && (waterOverlap < tileSize * 0.2f))
            {
                waterBuoyancy = transform->getVelocity().y > 0 ? defaultBuoyancy : bobbingBuoyancy;
            }
            else if (waterOverlap >= tileSize * 0.2f)
            {
                waterBuoyancy = defaultBuoyancy;
            }

            transform->addVelocityY(-waterBuoyancy * gravity * 0.01f);
        }
    }
}

void PhysicsManager::resolveCollisions(Transform *transform, Collider *collider, BoundingBox other)
{
    auto resolveAxis = [transform, collider](char axis, float overlap = 0.0f) -> void
    {
        if (axis == 'x')
        {
            transform->addX(-overlap);
            if ((overlap < 0 && transform->getVelocity().x < 0) || (overlap > 0 && transform->getVelocity().x > 0))
                transform->setVelocityX(0);
        }
        else
        {
            transform->addY(-overlap);
            if ((overlap < 0 && transform->getVelocity().y < 0) || (overlap > 0 && transform->getVelocity().y > 0))
                transform->setVelocityY(0);
        }

        collider->followTransform();
    };

    Vector overlap = collider->getOverlap(other);
    if (overlap.x == 0 && overlap.y == 0)
        return;

    if (overlap.y > 0)
        collider->setGrounded(true);

    fabs(overlap.x) < fabs(overlap.y) ? resolveAxis('x', overlap.x) : resolveAxis('y', overlap.y);
}

bool PhysicsManager::raycast(Vector origin, Vector direction, int length = -1)
{
    return false;
}