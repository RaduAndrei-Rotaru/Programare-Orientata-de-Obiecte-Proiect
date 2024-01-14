#pragma once
#include "animated_entity.h"

namespace rat_trappers
{
    class IngameState;
    class RatShot : public AnimatedEntity
    {
    public:

        RatShot() = delete;
        RatShot(const RatShot&) = delete;
        RatShot(RatShot&&) = delete;
        RatShot& operator=(const RatShot&) = delete;
        RatShot& operator=(RatShot&&) = delete;


        RatShot(Game& game, IngameState& state);
        ~RatShot() override = default;

        void update(unsigned long dt) override;

        virtual void fire();
        void explode();
        bool isReadyToBeFired() const;

        int getReloadRate() const;
    protected:
        IngameState& mState;
        int           mProgressTicks;
    };
}