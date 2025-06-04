#ifndef QTRESOURCES_H
#define QTRESOURCES_H

#include "resources/Resources.h"

namespace gt
{
    class QtTexture;

    class QtResources : public Resources
    {
    public:
        gref<Texture> texture(const char * path) override;
    };
}

#endif // QTRESOURCES_H
