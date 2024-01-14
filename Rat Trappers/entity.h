#pragma once
#include <SDL.h>

namespace rat_trappers
{
    class Game;
    class Entity
    {
    public:

        Entity() = delete;
        Entity(const Entity&) = delete;
        Entity(Entity&&) = delete;
        Entity& operator=(const Entity&) = delete;
        Entity& operator=(Entity&&) = delete;


        Entity(Game& game) : mGame(game), mRect({ 0,0,0,0 }) {}
        virtual ~Entity() = default;

        virtual void update(unsigned long dt) {}

        int getX()      const { return mRect.x; }
        int getY()      const { return mRect.y; }
        int getWidth()  const { return mRect.w; }
        int getHeight() const { return mRect.h; }

        const SDL_Rect& getRect() const { return mRect; }

        virtual void setX(int x) { mRect.x = x; }
        virtual void setY(int y) { mRect.y = y; }
        virtual void setWidth(int w) { mRect.w = w; }
        virtual void setHeight(int h) { mRect.h = h; }
    protected:
        Game& mGame;
    private:
        SDL_Rect mRect;
    };
}