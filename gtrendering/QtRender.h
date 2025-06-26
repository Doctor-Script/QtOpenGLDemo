#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

#include "gtengine/rendering/Render.h"

#include "gtrendering/QtShader.h"
#include "gtrendering/QtSpriteRenderDelegate.h"

namespace gt
{
    class QtRender : public Render
    {
    public:
//        QOpenGLBuffer arrayBuf;
//        QOpenGLBuffer indexBuf;

//        QtSpriteRenderDelegate spriteRenderDelegate;

        QtRender();
        ~QtRender();

//        void init() override;

        Shader* shader(const char* vertex, const char* fragment) override {
            qDebug() << "shader";
            return new QtShader(vertex, fragment);
        }
    };
}
