#pragma once
#include "animated_entity.h"

#include <array>

namespace rat_trappers
{
    class OshaRat : public AnimatedEntity
    {
    public:
        static const auto APPEAR_INTERVAL = 1200;
        static const std::array<int, 15> POINT_TABLE;


        OshaRat() = delete;
        OshaRat(const OshaRat&) = delete;
        OshaRat(OshaRat&&) = delete;
        OshaRat& operator=(const OshaRat&) = delete;
        OshaRat& operator=(OshaRat&&) = delete;


        OshaRat(Game& game);
        ~OshaRat() override = default;

        void update(unsigned long dt) override;

        void explode();
        void launch();

        int getPoints() const;

        int getAppearingCounter() const { return mAppearingCounter; }
    private:
        int mAppearingCounter;
    };
}