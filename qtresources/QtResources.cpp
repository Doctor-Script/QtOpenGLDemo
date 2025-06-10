#include "qtresources/QtResources.h"

#include "qtresources/QtTexture.h"

namespace gt
{
    gref<Texture> QtResources::texture(const char *path)
    {
        if (_loaded.count(path) > 0) {
            return s_cast<Texture>(_loaded[path]);
        }

        char fullPath[GT_RESOURCES_MAX_PATH] = ":/resources/";

        //TODO check full path length

        strncat(fullPath, path, GT_RESOURCES_MAX_PATH);
        printf("%s\n", fullPath);
        auto result = std::make_shared<QtTexture>(fullPath);
        _loaded.emplace(path, result);
        return result;
    }
}
