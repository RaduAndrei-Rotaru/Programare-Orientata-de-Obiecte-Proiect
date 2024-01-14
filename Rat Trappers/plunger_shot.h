#pragma once
#include "rat_shot.h"

#include <array>

namespace rat_trappers
{
    class IngameState;
    class PlungerShot final : public RatShot
    {
    public:
        static const std::array<int, 15> SHOT_COLUMNS;


        PlungerShot() = delete;
        PlungerShot(const PlungerShot&) = delete;
        PlungerShot(PlungerShot&&) = delete;
        PlungerShot& operator=(const PlungerShot&) = delete;
        PlungerShot& operator=(PlungerShot&&) = delete;


        PlungerShot(Game& game, IngameState& state);
        ~PlungerShot() override = default;

        void fire() override;
    private:
        int mNextShotColumnIndex;
    };
}