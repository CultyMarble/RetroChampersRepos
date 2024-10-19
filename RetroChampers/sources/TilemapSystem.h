#pragma once

namespace tms // Tile Map System
{
    class TilemapSystem
    {
    private:
        struct TileData
        {
        public:
            TileData(int x, int y, int idx, int idy, bool canPass)
                : textureIDx(idx), textureIDy(idy), canPass(canPass)
            {
                collisionBox = { 
                    static_cast<float>(x), static_cast<float>(y), 
                    static_cast<float>(SIZE), static_cast<float>(SIZE)
                };
            }

            Rectangle collisionBox = {};
            const int SIZE = 64;
            int textureIDx = {};
            int textureIDy = {};
            bool canPass = {};
        };

        TilemapSystem();
        static TilemapSystem* _instance;
        static const int _mapSize = 100;
        static const int _tileSize = 64;

    private:
        std::vector<TileData> map;

    public:
        static TilemapSystem* Get();
        virtual ~TilemapSystem();

        void LoadMapList(std::vector<char>& TileMapList);
        std::vector<TileData> GetMap() const;
    };

    class TileData
    {
        Rectangle collisionBox{};
        const float size = 64.0f;
        int textureIDx{};
        int textureIDy{};
        bool isPassable{};

    public:
        Rectangle GetCollisionBox() const { return collisionBox; }
        void SetCollisionBox(Rectangle newRec) { collisionBox = newRec; }

        float GetSize() const { return size; }

        int GetIDx() const { return textureIDx; }
        void SetIDx(int newID) { textureIDx = newID; }

        int GetIDy() const { return textureIDy; }
        void SetIDy(int newID) { textureIDy = newID; }

        bool IsPassable() const { return isPassable; }
        void SetPassable(const bool newBool) { isPassable = newBool; }
    };


}