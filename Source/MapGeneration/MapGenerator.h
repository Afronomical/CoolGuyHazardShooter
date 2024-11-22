#include <string>

class MapGenerator {
public:
	static std::weak_ptr<Map> LoadNextMap(const std::weak_ptr<Map> currentMap, const std::string& newMapName, const std::string& newMapPath);
};