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
    class QtRenderer;

    class SriteRenderDelegate : public RenderDelegate//, protected QOpenGLFunctions
    {
    public:
        QtRenderer* qtRenderer;
        QOpenGLShaderProgram program;
        QOpenGLTexture *texture;

        SriteRenderDelegate(QtRenderer* qtRenderer);

        void init() override;
//        void render(Renderable* renderable) override;
        void render(Renderable* renderable, Transform2D::Cache& cache) override;
    };

    class QtRenderer : public Renderer, public QOpenGLFunctions
    {
    public:

//        QOpenGLShaderProgram program;

//        QOpenGLTexture *texture;

        QMatrix4x4 projection;

        QOpenGLBuffer arrayBuf;
        QOpenGLBuffer indexBuf;

        SriteRenderDelegate sriteRenderDelegate;

        QtRenderer();
        ~QtRenderer();

        void init() override;
        void render(gref<GNode> scene) override;
        void resize(int w, int h) override;

//        void draw(gref<GNode> sprite, Transform2D::Global& parent);
    };




}

#endif // SRITERENDERDELEGATE_H
