#include <string>
#include "../FileHandling/FileHandler.h"
#include "../Debugging/Debug.h"
#include "../Map/Map.h"
#include "MapGenerator.h"



std::weak_ptr<Map> MapGenerator::LoadNextMap(const std::weak_ptr<Map> currentMap, const std::string& newMapName, const std::string& newMapPath) {
    if (!FileHandler::LoadMap(newMapName, newMapPath)) {
        Debug::LogError("Failed to load new map!");
        return {};
    }

    std::weak_ptr<Map> newMap = FileHandler::GetMap(newMapName);

    auto currentMapShared = currentMap.lock();

    int currentMapWidth = currentMapShared->GetColumns() * currentMapShared->GetTileSize();
    int currentMapHeight = currentMapShared->GetRows() * currentMapShared->GetTileSize();

    int newMapX = currentMapWidth;
    int newMapY = 0;

    return newMap;
};
