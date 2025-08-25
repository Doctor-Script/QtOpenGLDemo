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
        QString _prefix;
    public:
        ResourceLoader(Platform&);

        OpResult load(ResourceManager& manager, Texture::Builder& builder);

        OpResult load(ResourceManager& manager, Font::Builder& builder);
    };
}
