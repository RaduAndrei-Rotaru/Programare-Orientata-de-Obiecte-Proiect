#pragma once
#include "animated_entity.h"

namespace rat_trappers
{
    class Rat : public AnimatedEntity
    {
    public:
        static const int INITIAL_STEP_SIZE = 55;
        static const int STEP_DECREMENT_SIZE = 1;
        static const int RAT_PER_ROW = 11;


        Rat() = delete;
        Rat(const Rat&) = delete;
        Rat(Rat&&) = delete;
        Rat& operator=(const Rat&) = delete;
        Rat& operator=(Rat&&) = delete;


        Rat(Game& game, int index);
        ~Rat() override = default;

        void disappear();

        int getPoints() const { return mPoints; }
    private:
        int resolveYPosition();
    private:
        int mIndex;
        int mPoints;
    };
    typedef std::shared_ptr<Rat> RatPtr;
}