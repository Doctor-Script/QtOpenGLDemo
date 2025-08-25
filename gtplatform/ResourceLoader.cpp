#include "ResourceLoader.h"

#include "gtengine/resources/ResourceManager.h"

#include "gtengine/utils/types.h"
#include "gtengine/utils/Log.h"
#include "gtengine/utils/Color.h"

#include <QImage>

#include <QFile>
#include <QTextStream>
#include <sstream>


namespace gt
{
    ResourceLoader::ResourceLoader(Platform&) { }

    OpResult ResourceLoader::load(ResourceManager&, Texture::Builder& builder)
    {
        std::string prefix(":/resources/");
        auto name = builder.name();
        std::string fullPath = prefix.append(name);

        auto img = QImage(fullPath.c_str());
        const uchar* data = img.constBits();

        if (!data)
        {
            builder.rgba(Color::magenta().toRGBA(), 1, 1);
            FAIL_OP("Texture '%s' not found", name);
        }

        builder.fromFile(data, img.width(), img.height(), GL_BGRA);
        return OpResult::OK;
    }


    OpResult ResourceLoader::load(ResourceManager& manager, Font::Builder& builder)
    {
        auto name = builder.name();
        std::string prefix(":/resources/");
        std::string filename = prefix.append(name);


        QFile resourceFile(filename.c_str());
        if (!resourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            FAIL_OP("Font '%s' not found", name);
        }

        QTextStream qin(&resourceFile);
        QString content = qin.readAll();
        resourceFile.close();


        std::stringstream in;
        in << content.toStdString();

        std::string dir;
        size_t pos = filename.find_last_of("/\\");
        if (pos != std::string::npos) dir = filename.substr(0, pos+1);

        std::string line;
        while (std::getline(in, line)) {
            builder.line(line.c_str(), manager);
        }

        return OpResult::OK;
    }
}
