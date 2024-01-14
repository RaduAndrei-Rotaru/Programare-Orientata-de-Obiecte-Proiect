#include "rolling_shot.h"
#include "game.h"
#include "ingame_state.h"

#include <algorithm>

using namespace rat_trappers;

RollingShot::RollingShot(Game& game, IngameState& state) : RatShot(game, state), mLock(0)
{
    setImage(mGame.getSpriteSheet());
    setWidth(9);
    setHeight(21);
    setVelocity(0.2f);
    setDirectionY(1.f);
    addAnimationFrame("normal", { 149, 37, 9, 21 });
    addAnimationFrame("normal", { 163, 37, 9, 21 });
    addAnimationFrame("normal", { 149, 37, 9, 21 });
    addAnimationFrame("normal", { 178, 37, 9, 21 });
    addAnimationFrame("explode", { 218, 5, 18, 24 });
    setCurrentAnimation("normal");
    setAnimationStepSize(4);
    setVisible(false);
    setEnabled(false);
}

void RollingShot::update(unsigned long dt)
{
    if (mLock > 0) {
        mLock--;
    }
    RatShot::update(dt);
}

void RollingShot::fire()
{
    const auto& avatar = mState.getAvatar();
    const auto& rats = mState.getRats();

    const auto avatarX = avatar.getCenterX();
    auto ratIdx = -1;
    auto prevDistance = -1;
    for (auto col = 0; col < 11; col++) {
        auto distance = std::abs(rats[col]->getCenterX() - avatarX);
        if (prevDistance != -1 && distance > prevDistance) {
            break;
        }
        for (auto row = 4; row >= 0; row--) {
            auto idx = (row * 11) + col;
            if (rats[idx]->isVisible()) {
                ratIdx = idx;
                prevDistance = distance;
                break;
            }
        }
    }

    if (ratIdx != -1) {
        auto rat = rats[ratIdx];
        setX(rat->getCenterX() - getExtentX());
        setY(rat->getY() + rat->getHeight());
        RatShot::fire();
        mLock = getReloadRate() * 4;
    }
}