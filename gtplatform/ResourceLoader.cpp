#include "ResourceLoader.h"

#include "gtengine/utils/types.h"
#include "gtengine/utils/Log.h"

#include <QImage>


namespace gt
{
    ResourceLoader::ResourceLoader(Platform&) { }

    OpResult ResourceLoader::load(Resource::Name name, gref<Texture>& result)
    {
        std::string prefix(":/resources/");
        std::string fullPath = prefix.append(name);

        auto img = QImage(fullPath.c_str());
        const uchar* data = img.constBits();
        if (!data && !result->fallback())
        {
            Log::error("Texture '%s' not found", name);
            return OpResult::FAIL;
        }

        return result->fill(data, img.width(), img.height(), GL_BGRA);
    }
}
