#include "pch.h"
#include "tilemap_impl.h"
#include "mesh.h"
#include "texture.h"
#include "../log.h"

namespace Thsan {

    TilemapImpl::TilemapImpl() {
        mesh = create_mesh(0);
    }

    bool TilemapImpl::load(const int* data) {
        
        if (!data)
        {
            // Handle invalid input data, e.g., by returning false or throwing an exception
            return false;
        }

        // Calculate the total number of tiles in the data array
        const std::size_t totalTiles = tilemapWidth * tilemapHeight;

        // Resize the tileData vector to hold the data
        tileData.resize(totalTiles);

        // Create the mesh for the tilemap
        mesh = create_mesh(totalTiles * 4); // Each tile has four vertices

        // Create a vector to hold the vertices for the tilemap
        std::vector<Vertex> vertices;
        vertices.reserve(totalTiles * 4); // Reserve space for all vertices

        // Copy the tile data from the input array to tileData
        for (std::size_t i = 0; i < totalTiles; ++i)
        {
            tileData[i] = data[i];

            // Calculate texture coordinates using tileData and tileset_coordinates
            vec2f texCoords = tileset_coordinates[tileData[i]];

            // Create vertices for the current tile
            // Assuming each tile is a quad (two triangles)
            // You need to specify the positions and texture coordinates for each vertex
            // Here, we create vertices for a quad with each vertex having the same position
            // but different texture coordinates to map the tile from the texture.
            vertices.push_back(Vertex(vec3f(0.f, 0.f, 0.f),               vec3f(0.f, 0.f, -1.f), texCoords));
            vertices.push_back(Vertex(vec3f(tileWidth, 0.f, 0.f),         vec3f(0.f, 0.f, -1.f), vec2f(texCoords.x + 1.0f, texCoords.y)));
            vertices.push_back(Vertex(vec3f(tileWidth, tileHeight, 0.0f), vec3f(0.f, 0.f, -1.f), vec2f(texCoords.x + 1.0f, texCoords.y + 1.0f)));
            vertices.push_back(Vertex(vec3f(0.f, tileHeight, 0.0f),       vec3f(0.f, 0.f, -1.f), vec2f(texCoords.x,        texCoords.y + 1.0f)));
        }

        // Set the vertices for the mesh
        mesh->setVertices(vertices);

        return true;
    }


    void TilemapImpl::setSize(unsigned int width, unsigned int height) {

        tilemapWidth = width;
        tilemapHeight = height;

        tileData.resize(tilemapWidth * tilemapHeight, -1);
        mesh->resize(tilemapWidth * tilemapHeight * 4);
    }

    unsigned int TilemapImpl::getWidth() const {
        return tilemapWidth;
    }

    unsigned int TilemapImpl::getHeight() const {
        return tilemapHeight;
    }

    void TilemapImpl::setTileSize(unsigned int width, unsigned int height) {
        // Update the tile size if needed
        tileWidth = width;
        tileHeight = height;

        // You may need to update other related data or buffers
    }

    unsigned int TilemapImpl::getTileWidth() const {
        return tileWidth;
    }

    unsigned int TilemapImpl::getTileHeight() const {
        return tileHeight;
    }

    int TilemapImpl::getTileAt(unsigned int x, unsigned int y) const {

        if (x < tilemapWidth && y < tilemapHeight) {
            int index = y * tilemapWidth + x;
            return tileData[index];
        }
        else {
            TS_CORE_WARN("In TilemapImpl::getTileAt(unsigned int x, unsigned int y), coordinates are out of bounds.");
            return -1; // Return a default value or handle out-of-bounds as needed
        }
    }

    void TilemapImpl::setTileAt(unsigned int x, unsigned int y, int tileID) {
      
        if (x < tilemapWidth && y < tilemapHeight) {
            int index = y * tilemapWidth + x;
            tileData[index] = tileID;
        }
        else {
            TS_CORE_WARN("In TilemapImpl::setTileAt(unsigned int x, unsigned int y, int tileID), coordinates are out of bounds.");
        }
    }

    vec4f TilemapImpl::getTileColorAt(unsigned int x, unsigned int y) const {

        if (x < tilemapWidth && y < tilemapHeight) {
            int index = y * tilemapWidth + x;
            int meshIndex = index * 4;

            if (meshIndex >= 0 && meshIndex < mesh->getVertexCount())
                return (*mesh)[meshIndex].color;
            else {
                TS_CORE_WARN("In TilemapImpl::getTileColorAt(unsigned int x, unsigned int y), mesh index is out of bounds.");
            }
        }
        else {
            TS_CORE_WARN("In TilemapImpl::getTileColorAt(unsigned int x, unsigned int y), coordinates are out of bounds.");
        }

        return vec4f(1.0f, 1.0f, 1.0f, 1.0f); // Default white color
    }



    void TilemapImpl::setTileColorAt(unsigned int x, unsigned int y, vec4f color) {

        if (x < tilemapWidth && y < tilemapHeight) {
            int index = y * tilemapWidth + x;
            int meshIndex = index * 4;

            if (meshIndex >= 0 && meshIndex < mesh->getVertexCount()) {
                for (int i = 0; i < 4; i++)
                    (*mesh)[meshIndex + i].color = color;
               
                mesh->generate();
            }
            else {
                TS_CORE_WARN("In TilemapImpl::setTileColorAt(unsigned int x, unsigned int y, vec4f color), mesh index is out of bounds.");
            }
        }
        else {
            TS_CORE_WARN("In TilemapImpl::setTileColorAt(unsigned int x, unsigned int y, vec4f color), coordinates are out of bounds.");
        }
    }


    void TilemapImpl::clear()
    {
    }

    void TilemapImpl::resize(unsigned int newWidth, unsigned int newHeight)
    {
        std::vector<int> newTilemap(newWidth * newHeight);

        for (unsigned int y = 0; y < std::min(tilemapHeight, newHeight); ++y)
            for (unsigned int x = 0; x < std::min(tilemapWidth, newWidth); ++x)
                newTilemap[y * tilemapWidth + x] = tileData[y * tilemapWidth + x];

        // Update dimensions and replace the old tilemap
        tilemapWidth = newWidth;
        tilemapHeight = newHeight;
        tileData = std::move(newTilemap);
        mesh->resize(newWidth * newHeight * 4);
    }


    int* TilemapImpl::getRawTileData()
    {
        return tileData.data();
    }

    // Implement the rest of the virtual functions

    bool TilemapImpl::loadTileset(std::shared_ptr<Texture2D> tileset_texture)
    {
        if (!tileset_texture)
        {
            TS_CORE_WARN("In TilemapImpl::loadTileset(std::shared_ptr<Texture2D> tileset_texture), trying to pass a nullptr tileset_texture.");
            return false;
        }

        this->tileset_texture = tileset_texture;

        // Calculate the number of rows and columns in the tileset
        int columns = tileset_texture->getSize().x / tileWidth;
        int rows = tileset_texture->getSize().y / tileHeight;

        // Clear existing tileset coordinates
        tileset_coordinates.clear();

        // Fill in the tileset_coordinates map
        int tileID = 0;
        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < columns; ++x)
            {
                // Calculate the texture coordinates for the current tile
                vec2f min(static_cast<float>(x * tileWidth) / tileset_texture->getSize().x,
                    static_cast<float>(y * tileHeight) / tileset_texture->getSize().y);

                vec2f max(static_cast<float>((x + 1) * tileWidth) / tileset_texture->getSize().x,
                    static_cast<float>((y + 1) * tileHeight) / tileset_texture->getSize().y);

                tileset_coordinates[tileID++] = vec2f(min.x, min.y);
                tileset_coordinates[tileID++] = vec2f(max.x, min.y);
                tileset_coordinates[tileID++] = vec2f(max.x, max.y);
                tileset_coordinates[tileID++] = vec2f(min.x, max.y);
            }
        }

        return true;
    }


    void TilemapImpl::draw(const RenderTarget& target, const RenderStates2D& states) const 
    {
        target.draw(*mesh, states);
    }

    // Other private methods and member functions as needed

} // namespace Thsan
