#pragma once
#include "animated_entity.h"

namespace rat_trappers
{
    class Avatar : public AnimatedEntity
    {
    public:

        Avatar() = delete;
        Avatar(const Avatar&) = delete;
        Avatar(Avatar&&) = delete;
        Avatar& operator=(const Avatar&) = delete;
        Avatar& operator=(Avatar&&) = delete;


        Avatar(Game& game);
        ~Avatar() override = default;

        void explode();
        void reset();
    };
}