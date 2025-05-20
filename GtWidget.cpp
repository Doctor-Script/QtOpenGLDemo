#include "GtWidget.h"

namespace gt
{
    GtWidget::GtWidget(QWidget *parent) : QOpenGLWidget(parent), indexBuf(QOpenGLBuffer::IndexBuffer)
    {

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
        indexBuf.create();

        float vertices[] = {
            0.0f,  0.0f,  1.0f, 0.0f, 0.0f,  // v0
            255.0f, 0.0f,  1.0f, 0.33f, 0.0f, // v1
            0.0f,  255.0f,  1.0f, 0.0f, 0.5f,  // v2
            255.0f,  255.0f,  1.0f, 0.33f, 0.5f // v3
        };

        GLushort indices[] = { 0, 1, 2, 3, 2, 1 };

        arrayBuf.bind();
        arrayBuf.allocate(vertices, 20 * sizeof(float));

        indexBuf.bind();
        indexBuf.allocate(indices, 6 * sizeof(GLushort));

    }

    void GtWidget::resizeGL(int w, int h)
    {
        projection.setToIdentity();
        projection.ortho(0.0f,1.0f*w,0.0f,1.0f*h,0.5f,200.0f);
    }

    void GtWidget::paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        texture->bind();
        QMatrix4x4 matrix;
        matrix.translate(0.0, 0.0, -50.0);
        program.setUniformValue("mvp_matrix", projection * matrix);
        program.setUniformValue("texture", 0);

        arrayBuf.bind();
        indexBuf.bind();

        quintptr offset = 0;

        int vertexLocation = program.attributeLocation("a_position");
        program.enableAttributeArray(vertexLocation);
        //program.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
        program.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, 5 * sizeof(float));

        offset += sizeof(QVector3D);

        int texcoordLocation = program.attributeLocation("a_texcoord");
        program.enableAttributeArray(texcoordLocation);
//        program.setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));
        program.setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, 5 * sizeof(float));

//        glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
        glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, 0);
    }

} // namespace gt
