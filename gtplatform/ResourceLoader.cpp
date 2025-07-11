#include "ResourceLoader.h"

#include "gtengine/utils/types.h"

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

        // TODO Fail if no file found

        auto img = QImage(fullPath.c_str());
        result = std::make_shared<Texture>(name, img.constBits(), img.width(), img.height());



        return OpResult::OK;
    }
}
