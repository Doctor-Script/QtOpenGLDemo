#include "gtrendering/QtRender.h"

namespace gt
{
    QtRender::QtRender() :
        arrayBuf(QOpenGLBuffer::VertexBuffer),
        indexBuf(QOpenGLBuffer::IndexBuffer),
        spriteRenderDelegate(this)
    {
        delegates.sprite = &spriteRenderDelegate;
    }

    QtRender::~QtRender() {
        arrayBuf.destroy();
        indexBuf.destroy();
    }

    void QtRender::init()
    {
        Render::init();

        initializeOpenGLFunctions();


        glClearColor(0, 0, 0, 1);


//        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        arrayBuf.create();
        arrayBuf.bind();
        arrayBuf.allocate(20 * sizeof(float));

        indexBuf.create();
        indexBuf.bind();
        indexBuf.allocate(6 * sizeof(GLushort));
    }

    void QtRender::resize(int width, int height)
    {
        projection.setToIdentity();
        projection.ortho(0.0f, width, 0.0f, height, 0.5f, 200.0f);//TODO 0.5f, 200.0f??????????

        QMatrix4x4 matrix;
        matrix.translate(0.0, 0.0, -50.0);//TODO -50.0???????????????

        projection = projection * matrix;
    }
}
