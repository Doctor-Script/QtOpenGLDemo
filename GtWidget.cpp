#include "GtWidget.h"

namespace gt
{
    GtWidget::GtWidget(GtWindow* window, QWidget *parent)
        : QOpenGLWidget(parent), _window(window), indexBuf(QOpenGLBuffer::IndexBuffer)
    {

    }

    GtWidget::~GtWidget() {
        arrayBuf.destroy();
        indexBuf.destroy();
    }

    void GtWidget::initializeGL()
    {
        initializeOpenGLFunctions();

        glClearColor(0, 0, 0, 1);

        if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
            close();
        if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
            close();
        if (!program.link())
            close();
        if (!program.bind())
            close();

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

    void GtWidget::resizeGL(int w, int h)
    {
        projection.setToIdentity();
        projection.ortho(0.0f, 1.0f * w, 0.0f, 1.0f * h, 0.5f, 200.0f);
    }

    void GtWidget::paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture->bind();
        QMatrix4x4 matrix;
        matrix.translate(0.0, 0.0, -50.0);
        program.setUniformValue("mvp_matrix", projection * matrix);
        program.setUniformValue("texture", 0);

        for (int i = 0; i < 3; i++)
        {
            float d = 100 * i;
            float vertices[] = {
                d + 0.0f,   d + 0.0f,    1.0f, 0.0f,  0.0f,  // v0
                d + 255.0f, d + 0.0f,    1.0f, 0.33f, 0.0f, // v1
                d + 0.0f,   d + 255.0f,  1.0f, 0.0f,  0.5f,  // v2
                d + 255.0f, d + 255.0f,  1.0f, 0.33f, 0.5f // v3
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
    }

    void GtWidget::draw()
    {

    }
} // namespace gt
