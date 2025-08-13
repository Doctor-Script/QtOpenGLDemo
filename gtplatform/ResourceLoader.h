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

        template <typename T> OpResult late(ResourceManager& manager, gref<Resource> resource)
        {
            gref<T> specific = s_cast<T>(resource);
            return load(manager, specific->name(), specific);
        }

        OpResult load(ResourceManager& manager, Resource::Name name, gref<Texture>& result);
        OpResult load(ResourceManager& manager, Resource::Name name, gref<Font>& result);
    };
}
