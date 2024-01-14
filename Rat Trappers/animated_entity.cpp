#include "animated_entity.h"

#include <algorithm>

using namespace rat_trappers;

AnimatedEntity::AnimatedEntity(Game& game)
    : MovableEntity(game),
    mAnimationStepSize(0),
    mAnimationCounter(0),
    mAnimationFrameIndex(0)
{

}

void AnimatedEntity::update(unsigned long dt)
{
    MovableEntity::update(dt);
    if (mCurrentAnimation.size() > 1 && mAnimationStepSize > 0) {
        mAnimationCounter = std::max(0, mAnimationCounter - 1);
        if (mAnimationCounter <= 0) {
            auto nextFrame = ((mAnimationFrameIndex + 1) % mCurrentAnimation.size());
            setAnimationFrame(nextFrame);
            mAnimationCounter = mAnimationStepSize;
        }
    }
}

void AnimatedEntity::setAnimationStepSize(int stepSize)
{
    mAnimationStepSize = stepSize;
}

void AnimatedEntity::setCurrentAnimation(const std::string& name)
{
    if (mAnimations.find(name) != mAnimations.end()) {
        mCurrentAnimation = mAnimations[name];
        mAnimationCounter = mAnimationStepSize;
        setAnimationFrame(0);
    }
}

void AnimatedEntity::setAnimationFrame(unsigned int frameIndex)
{
    if (mCurrentAnimation.empty() == false) {
        frameIndex = std::min(mCurrentAnimation.size(), frameIndex);

        const auto& animationClip = mCurrentAnimation[frameIndex];

        auto centerX = getCenterX();
        auto centerY = getCenterY();

        setClip(animationClip);

        setCenterX(centerX);
        setCenterY(centerY);

        mAnimationFrameIndex = frameIndex;
    }
}

void AnimatedEntity::addAnimationFrame(const std::string& name, const SDL_Rect& rect)
{
    if (mAnimations.find(name) == mAnimations.end()) {
        mAnimations[name] = std::vector<SDL_Rect>();
    }

    mAnimations[name].push_back(rect);
}