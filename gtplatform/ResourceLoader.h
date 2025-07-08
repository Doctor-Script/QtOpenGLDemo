#pragma once

#include "gtengine/resources/Resource.h"
#include "gtengine/resources/Texture.h"

namespace gt
{
    class Platform;

    class ResourceLoader
    {
    public:
        ResourceLoader(Platform&);

        void load(Resource::Name name, gref<Texture>& result);
    };
}
