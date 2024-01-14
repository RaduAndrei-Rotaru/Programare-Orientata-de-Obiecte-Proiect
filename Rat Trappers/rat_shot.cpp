#include "rat_shot.h"
#include "game.h"
#include "player_context.h"
#include "ingame_state.h"

using namespace rat_trappers;

RatShot::RatShot(Game& game, IngameState& state) : AnimatedEntity(game), mState(state), mProgressTicks(0)
{
   
}

void RatShot::update(unsigned long dt)
{
    if (isVisible()) {
        AnimatedEntity::update(dt);
        mProgressTicks++;
    }
}

void RatShot::fire()
{
    setEnabled(true);
    setVisible(true);
    setCurrentAnimation("normal");
    setDirectionY(1.f);
    mProgressTicks = 1;
}

void RatShot::explode()
{
    setEnabled(false);
    setCurrentAnimation("explode");
    setDisappearCountdown(10);
    setDirectionY(0.f);
}

bool RatShot::isReadyToBeFired() const
{
    if (isVisible() == true) {
        return false;
    }

    const auto reloadRate = getReloadRate();

    const auto& rollingShot = mState.getRollingShot();
    const auto& plungerShot = mState.getPlungerShot();
    const auto& squigglyShot = mState.getSquigglyShot();

    if (this != &rollingShot && rollingShot.mProgressTicks > 0 && reloadRate >= rollingShot.mProgressTicks) {
        return false;
    }
    else if (this != &plungerShot && plungerShot.mProgressTicks > 0 && reloadRate >= plungerShot.mProgressTicks) {
        return false;
    }
    else if (this != &squigglyShot && squigglyShot.mProgressTicks > 0 && reloadRate >= squigglyShot.mProgressTicks) {
        return false;
    }
    return true;
}

int RatShot::getReloadRate() const
{
    const auto& ctx = mGame.getActivePlayerContext();
    const auto currentScore = ctx.getScore();

    if (currentScore <= 200) {
        return 48;
    }
    else if (currentScore <= 1000) {
        return 16;
    }
    else if (currentScore <= 2000) {
        return 11;
    }
    else if (currentScore <= 3000) {
        return 8;
    }
    else {
        return 7;
    }
}