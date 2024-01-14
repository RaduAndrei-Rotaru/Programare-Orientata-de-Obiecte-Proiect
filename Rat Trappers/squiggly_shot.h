#pragma once
#include "rat_shot.h"

#include <array>

namespace rat_trappers
{
    class IngameState;
    class SquigglyShot final : public RatShot
    {
    public:
        static const std::array<int, 15> SHOT_COLUMNS;


        SquigglyShot() = delete;
        SquigglyShot(const SquigglyShot&) = delete;
        SquigglyShot(SquigglyShot&&) = delete;
        SquigglyShot& operator=(const SquigglyShot&) = delete;
        SquigglyShot& operator=(SquigglyShot&&) = delete;


        SquigglyShot(Game& game, IngameState& state);
        ~SquigglyShot() override = default;

        void fire() override;
    private:
        int mNextShotColumnIndex;
    };
}