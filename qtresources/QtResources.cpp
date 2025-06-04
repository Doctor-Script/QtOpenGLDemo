#include "qtresources/QtResources.h"

#include "qtresources/QtTexture.h"

namespace gt
{
    gref<Texture> QtResources::texture(const char *path) {

        // TODO Chacher loaded resources
        // TODO Unify path (remove `:` from files in qt)

        return std::make_shared<QtTexture>(path);
    }
}
