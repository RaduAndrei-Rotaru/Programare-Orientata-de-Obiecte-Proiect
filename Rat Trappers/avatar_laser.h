#pragma once
#include "animated_entity.h"

namespace rat_trappers
{
    class AvatarLaser : public AnimatedEntity
    {
    public:

        AvatarLaser() = delete;
        AvatarLaser(const AvatarLaser&) = delete;
        AvatarLaser(AvatarLaser&&) = delete;
        AvatarLaser& operator=(const AvatarLaser&) = delete;
        AvatarLaser& operator=(AvatarLaser&&) = delete;


        AvatarLaser(Game& game);
        ~AvatarLaser() override = default;

        void explode();
    };
}