#include "rat.h"
#include "game.h"
#include "player_context.h"

using namespace rat_trappers;

Rat::Rat(Game& game, int index) : AnimatedEntity(game), mIndex(index), mPoints(0)
{
    setImage(game.getSpriteSheet());
    setDirectionX(1.f);
    setVelocity(0.4f);
    setAnimationStepSize(INITIAL_STEP_SIZE);
    setStepSize(INITIAL_STEP_SIZE);
    setY(resolveYPosition());
    setHeight(24);

    auto row = (index / RAT_PER_ROW);
    auto col = (index % RAT_PER_ROW);

    if (row == 0) {
        setWidth(24);
        setX(72 + col * 48);
        addAnimationFrame("normal", { 5, 62, 24, 24 });
        addAnimationFrame("normal", { 34, 62, 24, 24 });
        mPoints = 30;
    }
    else if (row < 3) {
        setWidth(33);
        setX(67 + col * 48);
        addAnimationFrame("normal", { 5, 33, 33, 24 });
        addAnimationFrame("normal", { 43, 33, 33, 24 });
        mPoints = 20;
    }
    else {
        setWidth(36);
        setX(66 + col * 48);
        addAnimationFrame("normal", { 5, 5, 36, 24 });
        addAnimationFrame("normal", { 46, 5, 36, 24 });
        mPoints = 10;
    }
    setCurrentAnimation("normal");
}

int Rat::resolveYPosition()
{
    const auto& ctx = mGame.getActivePlayerContext();
    const auto playerLevel = ctx.getLevel();

    auto y = 192;
    if (playerLevel > 1) {
        y += 48;
    }
    if (playerLevel > 2) {
        y += 24;
    }
    if (playerLevel > 3) {
        y += 24;
    }
    if (playerLevel > 5) {
        y += 24;
    }
    return y + (48 * (mIndex / RAT_PER_ROW));
}

void Rat::disappear()
{
    setEnabled(false);
    setVisible(false);
}