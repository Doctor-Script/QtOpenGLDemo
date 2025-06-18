#include "QtShader.h"

namespace gt
{
    QtShader::QtShader(const char *vertex, const char *fragment) : Shader(vertex, fragment)
    {
        // TODO No next step if prev is failed

        if (!_program.addCacheableShaderFromSourceCode(QOpenGLShader::Vertex, vertex)) {
            _ok = false;
            qDebug() << "Vertex shader failed";
            return;
        }

        if (!_program.addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, fragment)) {
            _ok = false;
            qDebug() << "Fragment shader failed";
            return;
        }

        if (!_program.link()) {
            _ok = false;
            qDebug() << "Link program failed";
            return;
        }
    }

    bool QtShader::use()
    {
        assert(_ok && "shader failded");
        if (!_program.bind()) {
            _ok = false;
            // TODO LOG
            return false;
        }
        return true;
    }
}
