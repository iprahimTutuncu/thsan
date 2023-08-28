#pragma once
#include "tilemap.h"


namespace Thsan {

    class TilemapImpl : public Tilemap {
    public:
        // Constructor
        TilemapImpl();

        // Destructor
        virtual ~TilemapImpl() = default;

        // Inherited from Tilemap
        bool load(const int* data) override;
        void setSize(unsigned int width, unsigned int height) override;
        unsigned int getWidth() const override;
        unsigned int getHeight() const override;
        void setTileSize(unsigned int width, unsigned int height) override;
        unsigned int getTileWidth() const override;
        unsigned int getTileHeight() const override;
        int getTileAt(unsigned int x, unsigned int y) const override;
        void setTileAt(unsigned int x, unsigned int y, int tileID) override;
        vec4f getTileColorAt(unsigned int x, unsigned int y) const override;
        void setTileColorAt(unsigned int x, unsigned int y, vec4f color) override;
        void clear() override;
        void resize(unsigned int newWidth, unsigned int newHeight) override;
        int* getRawTileData() override;
        bool loadTileset(std::shared_ptr<Texture2D> tileset_texture) override;

        void draw(const RenderTarget& target, const RenderStates2D& states) const override;

    private:
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Texture2D> tileset_texture;

        // Tilemap data
        std::vector<int> tileData;
        std::unordered_map<int, vec2f> tileset_coordinates;
        uint32_t tilemapWidth{0};
        uint32_t tilemapHeight{0};
        uint32_t tileWidth{0};
        uint32_t tileHeight{0};

    };
}