#include "ResourceLoader.h"

#include "gtengine/utils/types.h"
#include "gtengine/utils/Log.h"

#include <QImage>


namespace gt
{
    ResourceLoader::ResourceLoader(Platform&) { }

    OpResult ResourceLoader::load(Resource::Name name, gref<Texture>& result)
    {
//        GLubyte pixel[4] = { 255, 0, 0, 255 };
//        result = std::make_shared<Texture>(name, pixel, 1, 1);

        std::string prefix(":/resources/");
        std::string fullPath = prefix.append(name);

        auto img = QImage(fullPath.c_str());
        const uchar* data = img.constBits();
        if (!data) {
            FAIL_OP("Texture %s not found", name);
        }

        result = std::make_shared<Texture>(name, data, img.width(), img.height());
        return OpResult::OK;
    }
}
