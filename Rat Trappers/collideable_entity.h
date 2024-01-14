#pragma once
#include "entity.h"

namespace rat_trappers
{
    class CollideableEntity : public Entity
    {
    public:

        CollideableEntity() = delete;
        CollideableEntity(const CollideableEntity&) = delete;
        CollideableEntity(CollideableEntity&&) = delete;
        CollideableEntity& operator=(const CollideableEntity&) = delete;
        CollideableEntity& operator=(CollideableEntity&&) = delete;


        CollideableEntity(Game& game);
        virtual ~CollideableEntity();

        void setExtentX(int extentX);
        void setExtentY(int extentY);
        void setCenterX(int centerX);
        void setCenterY(int centerY);

        void setX(int x) override;
        void setY(int y) override;
        void setWidth(int width) override;
        void setHeight(int height) override;

        virtual bool collides(CollideableEntity& entity) const;
        bool contains(int x, int y) const;

        SDL_Rect intersection(const CollideableEntity& entity) const;

        int getExtentX() const { return mExtentX; }
        int getExtentY() const { return mExtentY; }
        int getCenterX() const { return mCenterX; }
        int getCenterY() const { return mCenterY; }
        bool isEnabled() const { return mEnabled; }

        void setEnabled(bool enabled) { mEnabled = enabled; }
    private:
        int  mExtentX;
        int  mExtentY;
        int  mCenterX;
        int  mCenterY;
        bool mEnabled;
    };
}