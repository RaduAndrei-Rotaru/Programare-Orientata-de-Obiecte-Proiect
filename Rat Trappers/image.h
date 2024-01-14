#pragma once
#include <memory>
#include <string>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Color;
struct _TTF_Font;

namespace rat_trappers
{
    class Image final
    {
    public:
        Image(SDL_Surface* surface, SDL_Texture* texture);
        ~Image();

        static std::shared_ptr<Image> fromFile(SDL_Renderer* renderer, const std::string& filename);
        static std::shared_ptr<Image> fromText(SDL_Renderer* renderer, const std::string& text, SDL_Color& color, _TTF_Font* font);
        static std::shared_ptr<Image> stream(SDL_Renderer* renderer, int pixelFormat, int width, int height);

        SDL_Surface* getSurface() { return mSurface; }
        const SDL_Surface* getSurface() const { return mSurface; }

        SDL_Texture* getTexture() { return mTexture; }
        const SDL_Texture* getTexture() const { return mTexture; }

        int getWidth()  const { return mWidth; }
        int getHeight() const { return mHeight; }
    private:
        SDL_Surface* mSurface;
        SDL_Texture* mTexture;
        int           mWidth;
        int           mHeight;
    };
    typedef std::shared_ptr<Image> ImagePtr;
}