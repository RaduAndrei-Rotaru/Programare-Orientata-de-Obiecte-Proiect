#pragma once
#include "state.h"
#include "text_entity.h"
#include "drawable_entity.h"

namespace rat_trappers
{
    class WelcomeState : public State
    {
    public:

        WelcomeState() = delete;
        WelcomeState(const WelcomeState&) = delete;
        WelcomeState(WelcomeState&&) = delete;
        WelcomeState& operator=(const WelcomeState&) = delete;
        WelcomeState& operator=(WelcomeState&&) = delete;


        WelcomeState(Game& game);
        virtual ~WelcomeState() override = default;

        void update(unsigned long dt);
        void render(SDL_Renderer& renderer);

        void onEnter();
        void onExit();

        void onKeyUp(SDL_KeyboardEvent& event);
        void onKeyDown(SDL_KeyboardEvent& event);
    private:
        TextEntity mPlayText;
        TextEntity mNameText;
        TextEntity mSinglePlayerText;
        TextEntity mMultiPlayerText;
        TextEntity mControlsText;
        TextEntity mTableCaptionText;
        TextEntity mTableRow1Text;
        TextEntity mTableRow2Text;
        TextEntity mTableRow3Text;
        TextEntity mTableRow4Text;

        DrawableEntity mTableRow1Sprite;
        DrawableEntity mTableRow2Sprite;
        DrawableEntity mTableRow3Sprite;
        DrawableEntity mTableRow4Sprite;
    };
}