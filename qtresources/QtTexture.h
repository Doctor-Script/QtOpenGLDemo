#ifndef QTTEXTURE_H
#define QTTEXTURE_H

#include "resources/Texture.h"
#include <GL/gl.h>
#include <QOpenGLTexture>

namespace gt
{
    class QtTexture : public Texture
    {
        GLuint _id;
//        QOpenGLTexture* _impl;
    public:
        QtTexture(std::string path);

        bool bind() override;
    };
}

#endif // QTTEXTURE_H
