#pragma once
#include "state.h"
#include "text_entity.h"

namespace rat_trappers
{
    class PlayPlayerState : public State
    {
    public:
        const int VISIBLITY_TICKS = (30 * 5);

        PlayPlayerState() = delete;
        PlayPlayerState(const PlayPlayerState&) = delete;
        PlayPlayerState(PlayPlayerState&&) = delete;
        PlayPlayerState& operator=(const PlayPlayerState&) = delete;
        PlayPlayerState& operator=(PlayPlayerState&&) = delete;


        PlayPlayerState(Game& game);
        virtual ~PlayPlayerState() override = default;

        void update(unsigned long dt);
        void render(SDL_Renderer& renderer);

        void onEnter();
        void onExit();

        void onKeyUp(SDL_KeyboardEvent& event);
        void onKeyDown(SDL_KeyboardEvent& event);
    private:
        int         mTickCounter;
        TextEntity  mText;
    };
}