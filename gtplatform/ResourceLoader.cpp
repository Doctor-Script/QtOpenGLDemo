#include "ResourceLoader.h"

#include "gtengine/resources/ResourceManager.h"

#include "gtengine/utils/Log.h"
#include "gtengine/utils/Color.h"

#include <QImage>

#include <QFile>
#include <QTextStream>


namespace gt
{
    ResourceLoader::ResourceLoader(Platform&) : _prefix(":/resources/") { }

    OpResult ResourceLoader::load(Texture::BaseBuilder& builder)
    {
        auto img = QImage(_prefix + builder.name());
        const uchar* data = img.constBits();

        if (!data)
        {
            builder.failed();
            FAIL_OP("Texture '%s' not found", builder.name());
        }

        builder.fromFile(data, img.width(), img.height(), GL_BGRA_EXT);
        // !!! If ASYNC: at this point builder can be deleted

        return OpResult::OK;
    }

    OpResult ResourceLoader::load(Font::BaseBuilder& builder)
    {
        QFile file(_prefix + builder.name());
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            builder.failed();
            FAIL_OP("Font '%s' not found", builder.name());
        }

        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            builder.parseLine(line.toStdString().c_str());
        }
        builder.complete();

        file.close();
        return OpResult::OK;
    }
}
