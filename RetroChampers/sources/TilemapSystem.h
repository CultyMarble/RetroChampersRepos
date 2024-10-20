#pragma once

namespace tms // Tile Map System
{
    class TilemapSystem final
    {
    private:
        // TILE STRUCT
        struct TileData final
        {
        public:
            Rectangle collisionBox;
            int textureIDx = -1;
            int textureIDy = -1;
            bool isPassable;

            TileData(int x, int y, int idx, int idy, bool canPass)
                : textureIDx(idx), textureIDy(idy), isPassable(canPass)
            {
                collisionBox =
                {
                    static_cast<float>(x), static_cast<float>(y),
                    static_cast<float>(TILE_SIZE), static_cast<float>(TILE_SIZE)
                };
            }
        };

        // MAP STRUCT
        struct Map final
        {
        public:
            std::vector<TileData> tileList;
            int mapW = 0;
            int mapH = 0;
        };

    public:
        // Singleton pattern
        static void StaticInitialize();
        static void StaticTerminate();
        static TilemapSystem* Get();
        TilemapSystem() = default;
        ~TilemapSystem() = default;

        void LoadMaps(const std::filesystem::path& filePath);

        void SetActiveMap(int mapIndex);
        std::vector<TileData>* GetActiveMapData() const;

        // Return a map tile at a given index (safe access to TileData)
        Rectangle GetTileCollisionBox(int index) const;
        bool IsTilePassable(int index) const;
        int GetTileTextureIDx(int index) const;
        int GetTileTextureIDy(int index) const;

    private:
        void ParseMapLayout(const std::vector<std::string>& mapLines, Map& map);

        static const int TILE_SIZE = 64;
        std::vector<Map> maps;
        std::vector<TileData>* currentMapData = nullptr;
    };
}