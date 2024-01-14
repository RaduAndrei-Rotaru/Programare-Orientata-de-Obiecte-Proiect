#include "game.h"
#include "text_entity.h"
#include "player_context.h"
#include "play_player_state.h"

#include <chrono>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace rat_trappers;

inline unsigned long currentMillis()
{
    using namespace std::chrono;
    return (unsigned long)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

Game::Game(int width, int height) : mState(State::NOT_INITED),
mRenderer(nullptr),
mWindow(nullptr),
mFont(nullptr),
mPreviousTick(0),
mDeltaAccumulator(0),
mScene(nullptr),
mSpriteSheet(nullptr),
mPlayerCount(1),
mActivePlayer(Player::PLAYER_1),
mHiScore(0),
mPlayerContext1(std::make_shared<PlayerContext>()),
mPlayerContext2(std::make_shared<PlayerContext>())
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }

    if (IMG_Init(IMG_INIT_PNG) == -1) {
        std::cerr << "Unable to initialize IMG: " << IMG_GetError() << std::endl;
        return;
    }

    if (TTF_Init() == -1) {
        std::cerr << "Unable to initialize TTF: " << TTF_GetError() << std::endl;
        return;
    }

    mWindow = SDL_CreateWindow("Rat Trappers", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr) {
        std::cerr << "Unable to create SDL window: " << SDL_GetError() << std::endl;
        return;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == nullptr) {
        std::cerr << "Unable to create SDL renderer: " << SDL_GetError() << std::endl;
        return;
    }

    mFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 28);
    if (mFont == nullptr) {
        std::cerr << "Unable to load font: " << TTF_GetError() << std::endl;
        return;
    }

    mSpriteSheet = Image::fromFile(mRenderer, "spritesheet.png");
    if (mSpriteSheet == nullptr) {
        std::cerr << "Unable to load sprite sheet from local filesystem." << std::endl;
        return;
    }

    mState = State::INITED;
}

Game::~Game()
{
    TTF_CloseFont(mFont);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int Game::run()
{
    if (mState != State::INITED && mState != State::STOPPED) {
        std::cerr << "Uanble to run the game as the game state is " << (int)mState << std::endl;
        return -1;
    }

    mScene = std::make_shared<Scene>(*this);

    SDL_Event event;
    mState = State::RUNNING;
    mPreviousTick = currentMillis();
    while (mState == State::RUNNING) {
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
            case SDL_QUIT:
                mState = State::STOPPED;
                break;
            case SDL_KEYDOWN:
                mScene->onKeyDown(event.key);
                break;
            case SDL_KEYUP:
                mScene->onKeyUp(event.key);
                break;
            }
        }

        auto millis = currentMillis();
        auto dt = (millis - mPreviousTick);
        mPreviousTick = millis;

        mDeltaAccumulator += dt;
        static const auto FPS = (1000l / 60l);
        if (mDeltaAccumulator >= FPS) {
            mScene->update(FPS);
            mDeltaAccumulator -= FPS;
        }

        SDL_SetRenderDrawColor(mRenderer, 0x78, 0x81, 0x6c, 0xff);
        SDL_RenderClear(mRenderer);
 
        mScene->render(*mRenderer);

        SDL_RenderPresent(mRenderer);
    }

    return 0;
}

void Game::setActivePlayer(Player player)
{
    mActivePlayer = player;
    if (mScene) {
        auto score1 = mScene->getScore1Text();
        auto score2 = mScene->getScore2Text();
        if (player == Player::PLAYER_1) {
            score1->setVisible(true);
            score1->blink();
            score2->setVisible(false);
        }
        else {
            score2->setVisible(true);
            score2->blink();
            score1->setVisible(false);
        }
        mScene->setState(std::make_shared<PlayPlayerState>(*this));
    }
}

PlayerContext& Game::getActivePlayerContext()
{
    return (mActivePlayer == Player::PLAYER_1 ? *mPlayerContext1 : *mPlayerContext2);
}

const PlayerContext& Game::getActivePlayerContext() const
{
    return (mActivePlayer == Player::PLAYER_1 ? *mPlayerContext1 : *mPlayerContext2);
}