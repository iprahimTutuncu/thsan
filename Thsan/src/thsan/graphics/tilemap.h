#pragma once
#include <string>
#include "../system/vector.h"
#include "drawable.h"


namespace Thsan {
    class THSAN_API Tilemap : public Drawable {
    public:
        virtual ~Tilemap() = default;

        virtual bool load(const int* data) = 0;

        virtual void setSize(unsigned int width, unsigned int height) = 0;

        virtual unsigned int getWidth() const = 0;
        virtual unsigned int getHeight() const = 0;

        virtual void setTileSize(unsigned int width, unsigned int height) = 0;

        virtual unsigned int getTileWidth() const = 0;
        virtual unsigned int getTileHeight() const = 0;

        virtual int getTileAt(unsigned int x, unsigned int y) const = 0;
        virtual void setTileAt(unsigned int x, unsigned int y, int tileID) = 0;

        virtual vec4f getTileColorAt(unsigned int x, unsigned int y) const = 0;
        virtual void setTileColorAt(unsigned int x, unsigned int y, vec4f color) = 0;

        virtual void clear() = 0;

        virtual void resize(unsigned int newWidth, unsigned int newHeight) = 0;

        virtual int* getRawTileData() = 0;

        virtual bool loadTileset(std::shared_ptr<Texture2D> tileset_texture) = 0;

    protected:
        // Hérité via Drawable
        virtual void draw(const RenderTarget& target, RenderStates2D& states) const = 0;

    };


    inline THSAN_API std::shared_ptr<Tilemap> create_tilemap();
}
