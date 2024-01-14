#include "player_context.h"

using namespace rat_trappers;

PlayerContext::PlayerContext() : mLevel(1), mScore(0), mLives(3), mShotCount(0), mRelaunchTimer(0)
{
	
}

void PlayerContext::reset()
{
	mLevel = 1;
	mScore = 0;
	mLives = 3;
	mShotCount = 0;
	mRelaunchTimer = 0;
	mRats.clear();
	mShields.clear();
}