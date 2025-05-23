#ifndef SRITERENDERDELEGATE_H
#define SRITERENDERDELEGATE_H

#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLWidget>

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include "gtengine/render/Render.h"
#include "gtengine.h"

namespace gt
{
    class QtRender;

    class SriteRenderDelegate : public Render::Delegate
    {
    public:
        QtRender* qtRenderer;
        QOpenGLShaderProgram program;
        QOpenGLTexture *texture;

        SriteRenderDelegate(QtRender* qtRenderer);

        void init();
        void perform(Render::Item* renderable, Transform2D::Cache& cache) override;
    };

    class QtRender : public Render, public QOpenGLFunctions
    {
    public:

//        QOpenGLShaderProgram program;

//        QOpenGLTexture *texture;

        QMatrix4x4 projection;

        QOpenGLBuffer arrayBuf;
        QOpenGLBuffer indexBuf;

        SriteRenderDelegate sriteRenderDelegate;

        QtRender();
        ~QtRender();

        void init() override;
        void draw(gref<GNode> scene) override;
        void resize(int w, int h) override;
    };
}

#endif // SRITERENDERDELEGATE_H
