#include "qtresources/QtTexture.h"

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>

namespace gt
{
    QtTexture::QtTexture(std::string path)
    {
        auto img = QImage(path.c_str());

        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, img.constBits());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // TODO Mipmaps
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }

    bool QtTexture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, _id);
        return true;
    }
}
