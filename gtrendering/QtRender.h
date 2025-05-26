#pragma once

#include <QOpenGLFunctions>
//#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include "gtengine/rendering/Render.h"
#include "gtrendering/QtSpriteRenderDelegate.h"

namespace gt
{
    class QtRender : public Render, public QOpenGLFunctions
    {
    public:

    //        QOpenGLShaderProgram program;

    //        QOpenGLTexture *texture;

        QMatrix4x4 projection;

        QOpenGLBuffer arrayBuf;
        QOpenGLBuffer indexBuf;

        QtSpriteRenderDelegate spriteRenderDelegate;

        QtRender();
        ~QtRender();

        void init() override;
        void draw(gref<Node> scene) override;
        void resize(int w, int h) override;
    };
}
