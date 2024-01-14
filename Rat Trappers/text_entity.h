#pragma once
#include "drawable_entity.h"

namespace rat_trappers
{
    class TextEntity : public DrawableEntity
    {
    public:
        const int DEFAULT_BLINK_COUNT = 30;
        const int DEFAULT_BLINK_FREQUENCY = 5;


        TextEntity() = delete;
        TextEntity(const TextEntity&) = delete;
        TextEntity(TextEntity&&) = delete;
        TextEntity& operator=(const TextEntity&) = delete;
        TextEntity& operator=(TextEntity&&) = delete;


        TextEntity(Game& game);
        virtual ~TextEntity();

        void update(unsigned long dt) override;

        void setText(const std::string& text);
        void setColor(const SDL_Color& color);

        void blink();

        void setBlinkCount(int count) { mBlinkCount = count; }
        void setBlinkFrequency(int frequency) { mBlinkFrequency = frequency; }

        const std::string& getText()  const { return mText; }
        const SDL_Color& getColor() const { return mColor; }
    private:
        std::string mText;
        SDL_Color   mColor;
        int         mBlinks;
        int         mBlinkTimer;
        int         mBlinkCount;
        int         mBlinkFrequency;
    };
}