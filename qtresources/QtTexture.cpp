#include "qtresources/QtTexture.h"

#include <GL/gl.h>

namespace gt
{
    QtTexture::QtTexture(std::string path)
    {
        auto img = QImage(path.c_str());

        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);

        // Upload texture data (assuming you have image data)
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.constBits());
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, img.constBits());

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

//        QOpenGLTexture _impl = new QOpenGLTexture(QImage(path.c_str()));
//        _impl->setMinificationFilter(QOpenGLTexture::Nearest);
//        _impl->setMagnificationFilter(QOpenGLTexture::Linear);
//        _impl->setWrapMode(QOpenGLTexture::Repeat);

//        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Nearest filtering
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // Linear filtering
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);      // Wrap mode
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//        stbi_image_free(data);
//        return textureID
    }

    bool QtTexture::bind()
    {
//        _impl->bind();
        glBindTexture(GL_TEXTURE_2D, _id);
        return true;
    }
}
