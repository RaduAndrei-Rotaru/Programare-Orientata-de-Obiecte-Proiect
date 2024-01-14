#pragma once
#include "state.h"
#include <memory>

struct SDL_Renderer;
struct SDL_KeyboardEvent;

namespace rat_trappers
{
    class TextEntity;
    class Game;
    class Scene
    {
    public:

        Scene() = delete;
        Scene(const Scene&) = delete;
        Scene(Scene&&) = delete;
        Scene& operator=(const Scene&) = delete;
        Scene& operator=(Scene&&) = delete;

        Scene(Game& game);
        ~Scene() = default;

        void update(unsigned long dt);
        void render(SDL_Renderer& renderer);

        void onKeyUp(SDL_KeyboardEvent& event);
        void onKeyDown(SDL_KeyboardEvent& event);

        void setState(StatePtr state);

        std::shared_ptr<TextEntity> getScore1Text() { return mScore1Text; }
        std::shared_ptr<TextEntity> getScore2Text() { return mScore2Text; }
    protected:
        Game& mGame;
        StatePtr  mState;

        std::shared_ptr<TextEntity> mScore1Caption;
        std::shared_ptr<TextEntity> mHiScoreCaption;
        std::shared_ptr<TextEntity> mScore2Caption;

        std::shared_ptr<TextEntity> mScore1Text;
        std::shared_ptr<TextEntity> mHiScoreText;
        std::shared_ptr<TextEntity> mScore2Text;
    };
    typedef std::shared_ptr<Scene> ScenePtr;
}