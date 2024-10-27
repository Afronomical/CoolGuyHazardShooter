#include "Asset.h"

unsigned int Asset::assetCount = 0;
Asset Asset::invalidAsset = Asset(-1, nullptr);

Asset::Asset() : id(assetCount++), filepath(nullptr)
{
}

Asset::Asset(int _id, const char* _filepath) : id(_id), filepath(_filepath)
{
}
