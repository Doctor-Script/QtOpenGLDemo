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

        QtSpriteRenderDelegate(QtRender* qtRenderer);

        void perform(Render::Item* renderable, Transform2D::Cache& cache) override;
    };
}
