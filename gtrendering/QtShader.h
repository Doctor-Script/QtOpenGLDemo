#ifndef QTSHADER_H
#define QTSHADER_H

#include <rendering/Shader.h>

#include <QOpenGLShaderProgram>

namespace gt
{
    class QtShader : public Shader
    {
    public:
        QOpenGLShaderProgram _program;

        QtShader(const char* vertex, const char* fragment);

        bool use() override;

        GLuint program() override {
            return _program.programId();
        }
    };
}

#endif // QTSHADER_H
