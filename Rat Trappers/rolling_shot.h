#pragma once
#include "rat_shot.h"

#include <array>

namespace rat_trappers
{
    class RollingShot final : public RatShot
    {
    public:

        RollingShot() = delete;
        RollingShot(const RollingShot&) = delete;
        RollingShot(RollingShot&&) = delete;
        RollingShot& operator=(const RollingShot&) = delete;
        RollingShot& operator=(RollingShot&&) = delete;


        RollingShot(Game& game, IngameState& state);
        ~RollingShot() override = default;

        void update(unsigned long dt) override;
        void fire() override;

        int getLock() const { return mLock; }
    private:
        int mLock;
    };
}