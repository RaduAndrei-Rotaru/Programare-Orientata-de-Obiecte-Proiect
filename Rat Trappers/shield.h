#pragma once
#include "drawable_entity.h"

#include <memory>

namespace rat_trappers
{
    class Shield : public DrawableEntity
    {
    public:

        Shield() = delete;
        Shield(const Shield&) = delete;
        Shield(Shield&&) = delete;
        Shield& operator=(const Shield&) = delete;
        Shield& operator=(Shield&&) = delete;


        Shield(Game& game);
        ~Shield() override = default;

        bool collides(CollideableEntity& entity) const;

        bool hasVisiblePixel(const DrawableEntity& entity, int x, int y) const;
        bool hasVisiblePixel(void* pixels, int pitch, int x, int y) const;
    };
    typedef std::shared_ptr<Shield> ShieldPtr;
}