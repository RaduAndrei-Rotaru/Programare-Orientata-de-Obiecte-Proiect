#pragma once
#include "avatar.h"
#include "avatar_laser.h"
#include "drawable_entity.h"
#include "state.h"
#include "text_entity.h"
#include "rat.h"
#include "OSHA_rat.h"
#include "plunger_shot.h"
#include "squiggly_shot.h"
#include "rolling_shot.h"
#include "shield.h"

#include <vector>

namespace rat_trappers
{
    class IngameState : public State
    {
    public:

        IngameState() = delete;
        IngameState(const IngameState&) = delete;
        IngameState(IngameState&&) = delete;
        IngameState& operator=(const IngameState&) = delete;
        IngameState& operator=(IngameState&&) = delete;


        IngameState(Game& game);
        virtual ~IngameState() override = default;

        void update(unsigned long dt);
        void render(SDL_Renderer& renderer);

        void onEnter();
        void onExit();

        void onKeyUp(SDL_KeyboardEvent& event);
        void onKeyDown(SDL_KeyboardEvent& event);

        const std::vector<RatPtr>& getRats() const { return mRats; }

        const Avatar& getAvatar() const { return mAvatar; }

        const PlungerShot& getPlungerShot() const { return mPlungerShot; }
        PlungerShot& getPlungerShot() { return mPlungerShot; }

        const SquigglyShot& getSquigglyShot() const { return mSquigglyShot; }
        SquigglyShot& getSquigglyShot() { return mSquigglyShot; }

        const RollingShot& getRollingShot() const { return mRollingShot; }
        RollingShot& getRollingShot() { return mRollingShot; }
    private:
        DrawableEntity          mFooterLine;
        Avatar                  mAvatar;
        CollideableEntity       mLeftOobDetector;
        CollideableEntity       mRightOobDetector;
        CollideableEntity       mTopOobDetector;
        AvatarLaser             mAvatarLaser;
        TextEntity              mLifesText;
        DrawableEntity          mLifeSprite1;
        DrawableEntity          mLifeSprite2;
        std::vector<RatPtr>     mRats;
        CollideableEntity       mRatLeftDirector;
        CollideableEntity       mRatRightDirector;
        TextEntity              mGameOverText;
        TextEntity              mGameOverInstructions;
        OshaRat                 mOshaRat;
        PlungerShot             mPlungerShot;
        SquigglyShot            mSquigglyShot;
        RollingShot             mRollingShot;
        std::vector<ShieldPtr>  mShields;
    };
}