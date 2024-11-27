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

    std::weak_ptr<Map> newMap = FileHandler::InitialiseMap(newMapName);
    auto newMapShared = newMap.lock();

    // Default position
    Vector2 newMapPosition{ 0, 0 };

    if (auto currentMapShared = currentMap.lock()) {
        // Calculate new map position based on current map
        int currentMapWidth = currentMapShared->GetColumns() * currentMapShared->GetTileSize();
        int currentMapHeight = currentMapShared->GetRows() * currentMapShared->GetTileSize();

        // Position the new map to the right of the current map
        Vector2 currentMapPosition = currentMapShared->GetPosition();
        newMapPosition = { currentMapPosition.X + currentMapWidth, currentMapPosition.Y};
    }


    newMapShared->SetPosition(newMapPosition);

    return newMap;
}


