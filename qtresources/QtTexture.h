#ifndef QTTEXTURE_H
#define QTTEXTURE_H

#include "resources/Texture.h"

#include <QOpenGLTexture>

namespace gt
{
    class QtTexture : public Texture
    {
        QOpenGLTexture* _impl;
    public:
        QtTexture(const char* path);

        bool bind() override;
    };
}

#endif // QTTEXTURE_H
