#include "ResourceLoader.h"

#include "gtengine/utils/types.h"
#include "gtengine/utils/Log.h"
//#include "gtengine/utils/Color.h"

#include <QImage>


namespace gt
{
    ResourceLoader::ResourceLoader(Platform&) { }

    OpResult ResourceLoader::load(Resource::Name name, gref<Texture>& result)
    {
        // For debug
        //result = std::make_shared<Texture>(name, Color::green().toRGBA(), 1, 1, GL_RGBA); return OpResult::OK;

        std::string prefix(":/resources/");
        std::string fullPath = prefix.append(name);

        auto img = QImage(fullPath.c_str());
        const uchar* data = img.constBits();
        if (!data) {
            FAIL_OP("Texture %s not found", name);
        }

        result = std::make_shared<Texture>(name, data, img.width(), img.height(), GL_BGRA);
        return OpResult::OK;
    }
}
