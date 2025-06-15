#pragma once

#include "resources/Resource.h"
#include "resources/Texture.h"

namespace gt
{
    class ResourceLoader
    {
    public:
        ResourceLoader();

        void load(Resource::Name name, gref<Texture>& result);
    };
}
