#include "gtrendering/QtRender.h"

namespace gt
{
    QtRender::QtRender() :
//        arrayBuf(QOpenGLBuffer::VertexBuffer),
//        indexBuf(QOpenGLBuffer::IndexBuffer),
        spriteRenderDelegate(this)
    {
        delegates.sprite = &spriteRenderDelegate;
    }

    QtRender::~QtRender() {
//        arrayBuf.destroy();
//        indexBuf.destroy();
    }

    /*
    void QtRender::init()
    {
        Render::init();

        initializeOpenGLFunctions();


//        glClearColor(0, 0, 0, 1);


//        //glEnable(GL_DEPTH_TEST);
//        glEnable(GL_CULL_FACE);

//        arrayBuf.create();
//        arrayBuf.bind();
//        arrayBuf.allocate(20 * sizeof(float));

//        indexBuf.create();
//        indexBuf.bind();
//        indexBuf.allocate(6 * sizeof(GLushort));
    }
    //*/
}
