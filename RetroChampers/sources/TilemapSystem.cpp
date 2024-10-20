#include "Precompiled.h"
#include "raylib.h"
#include "TilemapSystem.h"

using namespace tms;

namespace
{
    std::unique_ptr<TilemapSystem> sTilemapSystem;
}

void TilemapSystem::StaticInitialize()
{
    sTilemapSystem = std::make_unique<TilemapSystem>();
}

void TilemapSystem::StaticTerminate()
{
    sTilemapSystem->currentMapData = nullptr;
    sTilemapSystem->maps.clear();
    sTilemapSystem.reset();
}

TilemapSystem* TilemapSystem::Get()
{
    return sTilemapSystem.get();
}

void TilemapSystem::LoadMaps(const std::filesystem::path& filePath)
{
    // Iterate through all .txt files in the specified folder
    for (const auto& maptxt : std::filesystem::directory_iterator(filePath))
    {
        if (maptxt.path().extension() != ".txt")
            continue;

        std::ifstream file(maptxt.path());
        assert(file.is_open() && "Failed to open map file!");

        Map newMap;

        std::vector<std::string> mapLines;
        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty())
                continue;

            mapLines.push_back(line);
        }

        file.close();

        assert(!mapLines.empty() && "Map file is empty or invalid!");

        // Parse the map layout and fill the map struct
        ParseMapLayout(mapLines, newMap);

        // Add the new map to the list of maps
        maps.push_back(std::move(newMap));
    }
}

void TilemapSystem::SetActiveMap(int mapIndex)
{
    if (mapIndex < 0 || mapIndex >= maps.size())
    {
        std::cerr << "Error: Invalid map index: " << mapIndex << std::endl;
        currentMapData = nullptr;
        return;
    }

    currentMapData = &maps[mapIndex].tileList;
}

std::vector<TilemapSystem::TileData>* TilemapSystem::GetActiveMapData() const
{
    return currentMapData;
}

Rectangle TilemapSystem::GetTileCollisionBox(int index) const
{
    if (!currentMapData || index < 0 || index >= currentMapData->size())
    {
        std::cerr << "Error: Invalid tile index or no active map set." << std::endl;
        return Rectangle{ 0, 0, 0, 0 };
    }

    return (*currentMapData)[index].collisionBox;
}

bool TilemapSystem::IsTilePassable(int index) const
{
    if (!currentMapData || index < 0 || index >= currentMapData->size())
    {
        std::cerr << "Error: Invalid tile index or no active map set." << std::endl;
        return false;
    }

    return (*currentMapData)[index].isPassable;
}

int TilemapSystem::GetTileTextureIDx(int index) const
{
    if (currentMapData == nullptr || index < 0 || index >= currentMapData->size())
    {
        std::cerr << "Error: Invalid tile index or no active map set." << std::endl;
        return -1;
    }

    return (*currentMapData)[index].textureIDx;
}

int TilemapSystem::GetTileTextureIDy(int index) const
{
    if (currentMapData == nullptr || index < 0 || index >= currentMapData->size())
    {
        std::cerr << "Error: Invalid tile index or no active map set." << std::endl;
        return -1;
    }

    return (*currentMapData)[index].textureIDy;
}

void TilemapSystem::ParseMapLayout(const std::vector<std::string>& mapLines, Map& map)
{
    map.mapW = mapLines[0].size();
    map.mapH = mapLines.size();

    int x = 0;
    int y = 0;

    // Fill the tileList vector with TileData based on the map layout
    for (const auto& line : mapLines)
    {
        for (char tileChar : line)
        {
            switch (tileChar)
            {
            case '0': map.tileList.emplace_back(x, y, 0, 2, false); break;
            case '1': map.tileList.emplace_back(x, y, 1, 2, false); break;
            case '2': map.tileList.emplace_back(x, y, 2, 2, false); break;
            case '3': map.tileList.emplace_back(x, y, 3, 2, false); break;
            case '4': map.tileList.emplace_back(x, y, 0, 1, false); break;
            case '5': map.tileList.emplace_back(x, y, 1, 1, false); break;
            case '6': map.tileList.emplace_back(x, y, 2, 1, false); break;
            case '7': map.tileList.emplace_back(x, y, 3, 1, false); break;
            case '9': map.tileList.emplace_back(x, y, 4, 0, false); break;
            case 'a': map.tileList.emplace_back(x, y, 0, 0, true); break;
            case 'b': map.tileList.emplace_back(x, y, 1, 0, true); break;
            case 'c': map.tileList.emplace_back(x, y, 2, 0, true); break;
            case 'd': map.tileList.emplace_back(x, y, 3, 0, true); break;
            default: map.tileList.emplace_back(x, y, -1, -1, true); break;
            }

            x += TILE_SIZE;
        }
        x = 0;
        y += TILE_SIZE;
    }
}