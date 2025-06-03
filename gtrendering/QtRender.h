#pragma once

#include <QOpenGLFunctions>
//#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include "gtengine/rendering/Render.h"

#include "gtrendering/QtShader.h"
#include "gtrendering/QtSpriteRenderDelegate.h"

namespace gt
{
    class QtRender : public Render, public QOpenGLFunctions
    {
    public:
        QMatrix4x4 projection;

        QOpenGLBuffer arrayBuf;
        QOpenGLBuffer indexBuf;

        QtSpriteRenderDelegate spriteRenderDelegate;

        QtRender();
        ~QtRender();

        void init() override;

        Shader* shader(const char* vertex, const char* fragment) override {
            return new QtShader(vertex, fragment);
        }

        void draw(gref<Node> scene) override;
        void resize(int w, int h);
    };
}
