#include "qtresources/QtResources.h"

#include "qtresources/QtTexture.h"

namespace gt
{
    gref<Texture> QtResources::texture(std::string path)
    {
        if (_loaded.count(path) > 0) {
            return s_cast<Texture>(_loaded[path]);
        }

        std::string prefix(":/resources/");
        std::string fullPath = prefix.append(path);

//        char fullPath[GT_RESOURCES_MAX_PATH] = ":/resources/";

        //TODO check full path length

//        strncat(fullPath, path, GT_RESOURCES_MAX_PATH);
//        printf("%s\n", fullPath);
        auto result = std::make_shared<QtTexture>(fullPath);
        _loaded.emplace(path, result);
        return result;
    }
}
