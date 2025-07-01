#pragma once

#include "gtengine/resources/Resource.h"
#include "gtengine/resources/Texture.h"

namespace gt
{
    class ResourceLoader
    {
    public:
        ResourceLoader();

        void load(Resource::Name name, gref<Texture>& result);
    };
}
