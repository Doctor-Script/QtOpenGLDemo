#pragma once

#include <QOpenGLFunctions>

#define WRAP_GL static inline

namespace gt
{
    struct gl
    {
        static QOpenGLFunctions* _functions;

        WRAP_GL void GenTextures(GLsizei n, GLuint *textures) {
            ::glGenTextures(n, textures);
        }

        WRAP_GL void DeleteTextures(GLsizei n, const GLuint *textures) {
            ::glDeleteTextures(n, textures);
        }

        WRAP_GL void BindTexture(GLenum target, GLuint texture) {
            ::glBindTexture(target, texture);
        }

        WRAP_GL void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels) {
            ::glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
        }

        WRAP_GL void TexParameteri(GLenum target, GLenum pname, GLint param) {
            ::glTexParameteri(target, pname, param);
        }

        WRAP_GL void Clear(GLbitfield mask) {
            ::glClear(mask);
        }

        // TODO
        //PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;
        //glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
        //glGenerateMipmap(GL_TEXTURE_2D);
        WRAP_GL void GenerateMipmap(GLenum target) {
            _functions->glGenerateMipmap(target);
        }
    };
}
