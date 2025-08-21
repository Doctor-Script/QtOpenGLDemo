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
    public:
        ResourceLoader(Platform&);

        OpResult load(ResourceManager& manager, Resource::Name name, gref<Texture>& result);
        OpResult load(ResourceManager& manager, Resource::Name name, gref<Font>& result);
    };
}
