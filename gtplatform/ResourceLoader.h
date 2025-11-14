#pragma once

#include "gtengine/resources/Resource.h"
#include "gtengine/resources/Texture.h"
#include "gtengine/resources/Font.h"


namespace gt
{
    class ResourceManager;
    class Platform;

    class ResourceLoader
    {
        const QString _prefix;
    public:
        ResourceLoader(Platform&);

        OpResult load(Texture::BaseBuilder& builder);

        OpResult load(Font::BaseBuilder& builder);
    };
}
