#include "Asset.h"

unsigned int Asset::assetCount = 0;
Asset Asset::invalidAsset = Asset(-1, "");

Asset::Asset() : id(assetCount++), filepath("")
{
}

Asset::Asset(int _id, const std::string& _filepath) : id(_id), filepath(_filepath)
{
}
