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
        initializeOpenGLFunctions();

        glClearColor(0, 0, 0, 1);


        spriteRenderDelegate.init();


        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        arrayBuf.create();
        arrayBuf.bind();
        arrayBuf.allocate(20 * sizeof(float));

        indexBuf.create();
        indexBuf.bind();
        indexBuf.allocate(6 * sizeof(GLushort));
    }

    void QtRender::resize(int w, int h)
    {
        projection.setToIdentity();
        projection.ortho(0.0f, w, 0.0f, h, 0.5f, 200.0f);//TODO 0.5f, 200.0f??????????

        QMatrix4x4 matrix;
        matrix.translate(0.0, 0.0, -50.0);//TODO -50.0???????????????

        projection = projection * matrix;
    }

    void QtRender::draw(gref<GNode> scene)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Render::draw(scene);
    }
}
