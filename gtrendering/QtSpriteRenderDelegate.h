#pragma once

#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>

#include "gtengine/rendering/Render.h"

namespace gt
{
    class QtRender;

    class QtSpriteRenderDelegate : public Render::Delegate
    {
    public:
        QtRender* qtRenderer;
        QOpenGLTexture *texture;

        QtSpriteRenderDelegate(QtRender* qtRenderer);

        void init();
        void perform(Render::Item* renderable, Transform2D::Cache& cache) override;
    };
}
