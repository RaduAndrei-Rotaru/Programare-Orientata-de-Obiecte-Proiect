#pragma once
#include "scene.h"
#include "image.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct _TTF_Font;

namespace rat_trappers
{
    class PlayerContext;
    class Game final
    {
    public:
        enum class State { NOT_INITED, INITED, RUNNING, STOPPED };
        enum class Player { PLAYER_1, PLAYER_2 };
    public:

        Game() = delete;
        Game(const Game& game) = delete;
        Game(Game&&) = delete;

        Game& operator=(const Game&) = delete;
        Game& operator=(Game&&) = delete;


        Game(int width, int height);
        ~Game();

        int run();

        void setActivePlayer(Player player);

        PlayerContext& getActivePlayerContext();
        const PlayerContext& getActivePlayerContext() const;

        Player getActivePlayer() const { return mActivePlayer; }

        int getPlayerCount() const { return mPlayerCount; }
        void setPlayerCount(int playerCount) { mPlayerCount = playerCount; }

        int getHiScore() const { return mHiScore; }
        void setHiScore(int score) { mHiScore = score; }

        SDL_Window* getWindow() { return mWindow; }
        const SDL_Window* getWindow() const { return mWindow; }

        SDL_Renderer* getRenderer() { return mRenderer; }
        const SDL_Renderer* getRenderer() const { return mRenderer; }

        _TTF_Font* getFont() { return mFont; }
        const _TTF_Font* getFont() const { return mFont; }

        ScenePtr getScene() { return mScene; }
        const ScenePtr getScene() const { return mScene; }

        ImagePtr getSpriteSheet() { return mSpriteSheet; }
        const ImagePtr getSpriteSheet() const { return mSpriteSheet; }

        PlayerContext& getPlayerContext1() { return *mPlayerContext1; }
        const PlayerContext& getPlayerContext1() const { return *mPlayerContext1; }

        PlayerContext& getPlayerContext2() { return *mPlayerContext2; }
        const PlayerContext& getPlayerContext2() const { return *mPlayerContext2; }
    private:
        State         mState;
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;
        _TTF_Font* mFont;
        unsigned long mPreviousTick;
        unsigned long mDeltaAccumulator;
        ScenePtr      mScene;
        ImagePtr      mSpriteSheet;
        int           mPlayerCount;
        Player        mActivePlayer;
        int           mHiScore;
        std::shared_ptr<PlayerContext> mPlayerContext1;
        std::shared_ptr<PlayerContext> mPlayerContext2;
    };
}