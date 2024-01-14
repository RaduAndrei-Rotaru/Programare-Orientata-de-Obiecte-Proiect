#include "OSHA_rat.h"
#include "game.h"
#include "player_context.h"

using namespace rat_trappers;

const std::array<int, 15> OshaRat::POINT_TABLE = {
  100, 50, 50, 100, 150, 100, 100, 50, 300, 100, 100, 100, 50, 150, 100
};

OshaRat::OshaRat(Game& game)
    : AnimatedEntity(game),
    mAppearingCounter(APPEAR_INTERVAL)
{
    setImage(game.getSpriteSheet());
    setVelocity(0.15f);
    setEnabled(false);
    setVisible(false);
    setX(672 - 43);
    setY(145);
    setWidth(43);
    setHeight(19);
    addAnimationFrame("normal", { 5, 91, 43, 19 });
    addAnimationFrame("explode", { 54, 91, 66, 24 });
    setCurrentAnimation("normal");
}

void OshaRat::update(unsigned long dt)
{
    if (isVisible() == false) {
        mAppearingCounter--;
    }
    else {
        AnimatedEntity::update(dt);
    }
}

void OshaRat::explode()
{
    setDirectionX(0);
    setCurrentAnimation("explode");
    setDisappearCountdown(15);
}

void OshaRat::launch()
{
    const auto& ctx = mGame.getActivePlayerContext();
    const auto shotCount = ctx.getShotCount();

    if ((shotCount % 2) == 0) {
        setDirectionX(-1.f);
        setX(672 - getWidth());
    }
    else {
        setDirectionX(1.f);
        setX(0);
    }

    setEnabled(true);
    setVisible(true);
    setCurrentAnimation("normal");
    mAppearingCounter = APPEAR_INTERVAL;
}

int OshaRat::getPoints() const
{
    const auto& ctx = mGame.getActivePlayerContext();
    const auto shotCount = ctx.getShotCount();

    return POINT_TABLE[shotCount % 15];
}