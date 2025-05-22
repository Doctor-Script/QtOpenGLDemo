#include "SriteRenderDelegate.h"

#include "gtengine/sprite/Transform2D.h"

namespace gt
{
    QtRenderer::QtRenderer() : arrayBuf(QOpenGLBuffer::VertexBuffer), indexBuf(QOpenGLBuffer::IndexBuffer)
    {

    }

    QtRenderer::~QtRenderer() {
        arrayBuf.destroy();
        indexBuf.destroy();
    }

    void QtRenderer::init()
    {
        initializeOpenGLFunctions();

        glClearColor(0, 0, 0, 1);

        if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
//            close();
            return;
        if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
//            close();
            return;
        if (!program.link())
//            close();
            return;
        if (!program.bind())
//            close();
            return;

        texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());
        texture->setMinificationFilter(QOpenGLTexture::Nearest);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        texture->setWrapMode(QOpenGLTexture::Repeat);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        arrayBuf.create();
        arrayBuf.bind();
        arrayBuf.allocate(20 * sizeof(float));

        indexBuf.create();
        indexBuf.bind();
        indexBuf.allocate(6 * sizeof(GLushort));
    }

    void QtRenderer::resize(int w, int h)
    {
        projection.setToIdentity();
        projection.ortho(0.0f, 1.0f * w, 0.0f, 1.0f * h, 0.5f, 200.0f);
    }

    void QtRenderer::render(gref<GNode> scene)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture->bind();
        QMatrix4x4 matrix;
        matrix.translate(0.0, 0.0, -50.0);
        program.setUniformValue("mvp_matrix", projection * matrix);
        program.setUniformValue("texture", 0);

        Transform2D::Global none;
        FOREACH_NODE(node, scene) {
            draw(node->to<GNode2D>(), none);
        }
    }

    void QtRenderer::draw(gref<GNode2D> sprite, Transform2D::Global& parent)
    {
        auto spriteGlobal = sprite->transform.globalOf(parent);
        auto q = sprite->transform.vertices();

        FOREACH_NODE(node, sprite)
        {
            draw(node->to<GNode2D>(), spriteGlobal);
        }

//        qDebug() << q.bl.x << ", " << q.bl.y;
//        qDebug() << q.br.x << ", " << q.br.y;
//        qDebug() << q.tr.x << ", " << q.tr.y;
//        qDebug() << q.tl.x << ", " << q.tl.y;
//        qDebug() << "--------------------";

        float vertices[] = {
            q.bl.x, q.bl.y, 1.0f, 0.0f,  0.0f, // v0
            q.br.x, q.br.y, 1.0f, 0.33f, 0.0f, // v1
            q.tr.x, q.tr.y, 1.0f, 0.0f,  0.5f, // v2
            q.tl.x, q.tl.y, 1.0f, 0.33f, 0.5f  // v3
        };

        auto ptrV = arrayBuf.map(QOpenGLBuffer::WriteOnly);
        memcpy(ptrV, vertices, 20 * sizeof(float));
        arrayBuf.unmap();
        arrayBuf.bind();

        GLushort indices[] = { 0, 1, 2, 3, 2, 1 };
        auto ptrI = indexBuf.map(QOpenGLBuffer::WriteOnly);
        memcpy(ptrI, indices, 6 * sizeof(GLushort));
        indexBuf.unmap();
        indexBuf.bind();

        quintptr offset = 0;

        int vertexLocation = program.attributeLocation("a_position");
        program.enableAttributeArray(vertexLocation);
        program.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, 5 * sizeof(float));

        offset += sizeof(QVector3D);

        int texcoordLocation = program.attributeLocation("a_texcoord");
        program.enableAttributeArray(texcoordLocation);
        program.setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, 5 * sizeof(float));

        glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, 0);


    }



    SriteRenderDelegate::SriteRenderDelegate()
    {

    }
}
