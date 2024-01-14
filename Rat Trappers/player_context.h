#pragma once
#include "rat.h"
#include "shield.h"

#include <vector>

namespace rat_trappers
{
    class PlayerContext
    {
    public:

        PlayerContext(const PlayerContext&) = delete;
        PlayerContext(PlayerContext&&) = delete;
        PlayerContext& operator=(const PlayerContext&) = delete;
        PlayerContext& operator=(PlayerContext&&) = delete;

 

        PlayerContext();

        void reset();

        void addScore(int score) { mScore += score; }

        void setLevel(int level) { mLevel = level; }
        void setScore(int score) { mScore = score; }
        void setLives(int lives) { mLives = lives; }
        void setShotCount(int count) { mShotCount = count; }
        void setRelaunchTimer(int timer) { mRelaunchTimer = timer; }
        void setRats(const std::vector<RatPtr>& rats) { mRats = rats; }
        void setShields(const std::vector<ShieldPtr>& shields) { mShields = shields; }

        int getLevel() const { return mLevel; }
        int getScore() const { return mScore; }
        int getLives() const { return mLives; }
        int getShotCount() const { return mShotCount; }
        int getRelaunchTimer() const { return mRelaunchTimer; }
        const std::vector<RatPtr>& getRats() const { return mRats; }
        const std::vector<ShieldPtr>& getShields() const { return mShields; }
    private:
        int mLevel;
        int mScore;
        int mLives;
        int mShotCount;
        int mRelaunchTimer;
        std::vector<RatPtr> mRats;
        std::vector<ShieldPtr> mShields;
    };
}