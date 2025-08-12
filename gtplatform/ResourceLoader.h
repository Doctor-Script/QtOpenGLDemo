#pragma once

#include "gtengine/resources/Resource.h"
#include "gtengine/resources/Texture.h"
#include "gtengine/resources/Font.h"


namespace gt
{
    class Platform;

    class ResourceLoader
    {
    public:
        ResourceLoader(Platform&);

        template <typename T> OpResult late(gref<Resource> resource)
        {
            gref<T> specific = s_cast<T>(resource);
            return load(specific->name(), specific);
        }

        OpResult load(Resource::Name name, gref<Texture>& result);
        OpResult load(Resource::Name name, gref<Font>& result);
    };
}
