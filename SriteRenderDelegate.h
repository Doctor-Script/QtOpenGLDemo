#ifndef SRITERENDERDELEGATE_H
#define SRITERENDERDELEGATE_H

#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLWidget>

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include "gtengine/render/RenderDelegate.h"
#include "gtengine.h"
//#include "gtengine/GWindow.h"

namespace gt
{
    class QtRenderer : public Renderer, protected QOpenGLFunctions
    {
    public:
        QOpenGLShaderProgram program;

        QOpenGLTexture *texture;

        QMatrix4x4 projection;

        QOpenGLBuffer arrayBuf;
        QOpenGLBuffer indexBuf;

        QtRenderer();
        ~QtRenderer();

        void init() override;
        void render(gref<GNode> scene) override;
        void resize(int w, int h) override;

        void draw(gref<GNode2D> sprite, Transform2D::Global& parent);
    };

    class SriteRenderDelegate : public RenderDelegate, protected QOpenGLFunctions
    {
    public:



        SriteRenderDelegate();


    };
}

#endif // SRITERENDERDELEGATE_H
