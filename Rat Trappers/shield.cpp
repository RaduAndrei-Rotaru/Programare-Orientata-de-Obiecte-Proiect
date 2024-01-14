#include "shield.h"
#include "animated_entity.h"
#include "game.h"

#include <iostream>

using namespace rat_trappers;

Shield::Shield(Game& game) : DrawableEntity(game)
{
    auto spriteSheet = mGame.getSpriteSheet();
    Uint32 format(0);
    if (SDL_QueryTexture(spriteSheet->getTexture(), &format, nullptr, nullptr, nullptr) != 0) {
        std::cerr << "Unable to get sprite sheet format: " << SDL_GetError() << std::endl;
        return;
    }

    const auto& renderer = mGame.getRenderer();
    auto image = Image::stream(renderer, format, 66, 48);
    const auto& texture = image->getTexture();

    Uint32* pixels = nullptr;
    auto pitch = 0;
    if (SDL_LockTexture(texture, nullptr, (void**)&pixels, &pitch)) {
        std::cerr << "Unable to lock texture: " << SDL_GetError() << std::endl;
        return;
    }

    auto srcSurface = spriteSheet->getSurface();
    const auto srcPitch = srcSurface->pitch;
    Uint32* srcPixels = (Uint32*)srcSurface->pixels;

    auto clipX = 293;
    auto clipY = 5;
    auto bpp = srcSurface->format->BytesPerPixel;
    auto rowSize = (bpp * 66);
    for (auto i = 0; i < 48; i++) {
        auto dstOffset = i * pitch / bpp;
        auto srcOffset = (clipY + i) * srcPitch / bpp + clipX;
        SDL_memcpy(pixels + dstOffset, srcPixels + srcOffset, rowSize);
    }

    SDL_UnlockTexture(texture);

    setImage(image);
    setClip({ 0,0, 66,48 });

}

bool Shield::collides(CollideableEntity& entity) const
{
    if (CollideableEntity::collides(entity)) {
        auto rect = intersection(entity);
        if (rect.w == 0 && rect.h == 0) {
            return false;
        }
        else {
            SDL_Rect normalizedA = normalize(rect);
            SDL_Rect normalizedB = (static_cast<const DrawableEntity&>(entity)).normalize(rect);

            Uint32* pixels = nullptr;
            auto pitch = 0;
            const auto& texture = getImage()->getTexture();
            if (SDL_LockTexture(texture, nullptr, (void**)&pixels, &pitch)) {
                std::cerr << "Unable to lock texture: " << SDL_GetError() << std::endl;
                return false;
            }

            auto hasCollision = false;
            for (auto y = 0; y < rect.h; y++) {
                for (auto x = 0; x < rect.w; x++) {
                    if (hasVisiblePixel(pixels, pitch, normalizedA.x + x, normalizedA.y + y)) {
                        if (hasVisiblePixel((static_cast<const DrawableEntity&>(entity)), normalizedB.x + x, normalizedB.y + y)) {
                            hasCollision = true;
                            break;
                        }
                    }
                }
            }

            if (hasCollision) {
                auto& animatedEntity = static_cast<AnimatedEntity&>(entity);
                if (animatedEntity.getDirectionY() > 0.f) {
                    animatedEntity.setY(animatedEntity.getY() + 6);
                }
                animatedEntity.setCurrentAnimation("explode");
                animatedEntity.render(*mGame.getRenderer());

                rect = intersection(animatedEntity);
                normalizedA = normalize(rect);
                normalizedB = animatedEntity.normalize(rect);

                for (auto y = 0; y < rect.h; y++) {
                    for (auto x = 0; x < rect.w; x++) {
                        if (hasVisiblePixel(pixels, pitch, normalizedA.x + x, normalizedA.y + y)) {
                            if (hasVisiblePixel(animatedEntity, normalizedB.x + x, normalizedB.y + y)) {
                                Uint8* pixel = (Uint8*)pixels;
                                pixel += ((normalizedA.y + y) * pitch) + (normalizedA.x + x) * sizeof(Uint32);
                                SDL_PixelFormat* format = mGame.getSpriteSheet()->getSurface()->format;
                                *(Uint32*)pixel = SDL_MapRGBA(format, 0x78, 0x81, 0x6c, 0xff);
                            }
                        }
                    }
                }
            }

            SDL_UnlockTexture(texture);
            return hasCollision;
        }
        return true;
    }
    return false;
}

bool Shield::hasVisiblePixel(const DrawableEntity& entity, int x, int y) const
{
    auto surface = entity.getImage()->getSurface();
    return hasVisiblePixel(surface->pixels, surface->pitch, x, y);
}

bool Shield::hasVisiblePixel(void* pixels, int pitch, int x, int y) const
{
    auto bpp = 4;
    Uint8* p = (Uint8*)pixels + y * pitch + x * bpp;
    Uint32 pixelColor;

    switch (bpp)
    {
    case(1):
        pixelColor = *p;
        break;
    case(2):
        pixelColor = *(Uint16*)p;
        break;
    case(3):
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            pixelColor = p[0] << 16 | p[1] << 8 | p[2];
        else
            pixelColor = p[0] | p[1] << 8 | p[2] << 16;
        break;
    case(4):
        pixelColor = *(Uint32*)p;
        break;
    }

    SDL_PixelFormat* format = mGame.getSpriteSheet()->getSurface()->format;
    Uint8 red, green, blue, alpha;
    SDL_GetRGBA(pixelColor, format, &red, &green, &blue, &alpha);

    return alpha > 200;
}