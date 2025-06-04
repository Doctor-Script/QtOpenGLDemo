#include "qtresources/QtTexture.h"

namespace gt
{
    QtTexture::QtTexture(const char* path)
    {
        _impl = new QOpenGLTexture(QImage(path));
        _impl->setMinificationFilter(QOpenGLTexture::Nearest);
        _impl->setMagnificationFilter(QOpenGLTexture::Linear);
        _impl->setWrapMode(QOpenGLTexture::Repeat);
    }

    bool QtTexture::bind()
    {
        _impl->bind();
        return true;
    }
}
