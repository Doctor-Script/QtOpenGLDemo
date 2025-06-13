#include "ResourceLoader.h"

#include <QImage>

namespace gt
{
    ResourceLoader::ResourceLoader()
    {

    }

    void ResourceLoader::load(Resource::Name name, gref<Texture>& result)
    {
        std::string prefix(":/resources/");
        std::string fullPath = prefix.append(name);
        auto img = QImage(fullPath.c_str());
        result = std::make_shared<Texture>(fullPath.c_str(), img.constBits(), img.width(), img.height());
    }
}
