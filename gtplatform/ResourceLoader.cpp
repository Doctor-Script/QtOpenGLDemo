#include "ResourceLoader.h"

#include "gtengine/utils/types.h"
#include "gtengine/utils/Log.h"

#include <QImage>


namespace gt
{
    ResourceLoader::ResourceLoader(Platform&) { }

    OpResult ResourceLoader::load(Resource::Name name, gref<Texture>& texture)
    {
        std::string prefix(":/resources/");
        std::string fullPath = prefix.append(name);

        auto img = QImage(fullPath.c_str());
        const uchar* data = img.constBits();
        if (!data && !texture->fallback()) {
            FAIL_OP("Texture '%s' not found", name);
        }

        return texture->fill(data, img.width(), img.height(), GL_BGRA);
    }

    OpResult ResourceLoader::load(Resource::Name name, gref<Font>& font)
    {
        GT_LOG("here %s", name);
        GT_LOG("!!!! Loading font");
        return OpResult::OK;
    }
}
