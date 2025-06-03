#include "gtrendering/QtSpriteRenderDelegate.h"

#include "gtrendering/QtRender.h"
#include "planar/Sprite.h"

namespace gt
{
    QtSpriteRenderDelegate::QtSpriteRenderDelegate(QtRender* qtRenderer)
    {
        this->qtRenderer = qtRenderer;
    }

    void QtSpriteRenderDelegate::init()
    {
        texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());
        texture->setMinificationFilter(QOpenGLTexture::Nearest);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        texture->setWrapMode(QOpenGLTexture::Repeat);
    }

    void QtSpriteRenderDelegate::perform(Render::Item* renderable, Transform2D::Cache& cache)
    {
        Sprite* sprite = static_cast<Sprite*>(renderable);
        auto shader = static_cast<QtShader*>(sprite->shader);
        shader->use();

        float halfW = sprite->transform.width() / 2.0f;
        float halfH = sprite->transform.height() / 2.0f;


            // TODO one rotation
        Vector2 bl = cache.position + Vector2(-halfW, -halfH).rotate(cache.angle);
        Vector2 br = cache.position + Vector2( halfW, -halfH).rotate(cache.angle);
        Vector2 tr = cache.position + Vector2(-halfW,  halfH).rotate(cache.angle);
        Vector2 tl = cache.position + Vector2( halfW,  halfH).rotate(cache.angle);



        float vertices[] = {
            bl.x, bl.y, 1.0f, 0.0f,  0.0f, // v0
            br.x, br.y, 1.0f, 0.33f, 0.0f, // v1
            tr.x, tr.y, 1.0f, 0.0f,  0.5f, // v2
            tl.x, tl.y, 1.0f, 0.33f, 0.5f  // v3
        };

        auto ptrV = qtRenderer->arrayBuf.map(QOpenGLBuffer::WriteOnly);
        memcpy(ptrV, vertices, 20 * sizeof(float));
        qtRenderer->arrayBuf.unmap();
        qtRenderer->arrayBuf.bind();

        GLushort indices[] = { 0, 1, 2, 3, 2, 1 };
        auto ptrI = qtRenderer->indexBuf.map(QOpenGLBuffer::WriteOnly);
        memcpy(ptrI, indices, 6 * sizeof(GLushort));
        qtRenderer->indexBuf.unmap();
        qtRenderer->indexBuf.bind();

        texture->bind();

        // Set modelview-projection matrix
        shader->_program.setUniformValue("mvp_matrix", qtRenderer->projection);

        quintptr offset = 0;

        int vertexLocation = shader->_program.attributeLocation("a_position");
        shader->_program.enableAttributeArray(vertexLocation);
        shader->_program.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, 5 * sizeof(float));

        offset += sizeof(QVector3D);

        int texcoordLocation = shader->_program.attributeLocation("a_texcoord");
        shader->_program.enableAttributeArray(texcoordLocation);
        shader->_program.setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, 5 * sizeof(float));

        qtRenderer->glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, 0);
    }
}
