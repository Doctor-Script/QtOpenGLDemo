#pragma once

#include <QOpenGLFunctions>


namespace gt
{
#define WRAP_GL static inline
#define NATIVEGL(f) ::f
#define QTGL(f) _functions->f

    struct gl
    {
        static QOpenGLFunctions* _functions;

        WRAP_GL void GenTextures(GLsizei n, GLuint *textures) {
            NATIVEGL(glGenTextures(n, textures));
        }

        WRAP_GL void DeleteTextures(GLsizei n, const GLuint *textures) {
            NATIVEGL(glDeleteTextures(n, textures));
        }

        WRAP_GL void BindTexture(GLenum target, GLuint texture) {
            NATIVEGL(glBindTexture(target, texture));
        }

        WRAP_GL void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels) {
            NATIVEGL(glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels));
        }

        WRAP_GL void TexParameteri(GLenum target, GLenum pname, GLint param) {
            NATIVEGL(glTexParameteri(target, pname, param));
        }

        WRAP_GL void ClearColor(GLclampf red,GLclampf green,GLclampf blue,GLclampf alpha) {
            NATIVEGL(glClearColor(red, green, blue, alpha));
        }

        WRAP_GL void Clear(GLbitfield mask) {
            NATIVEGL(glClear(mask));
        }

         WRAP_GL void Enable(GLenum cap) {
            NATIVEGL(glEnable(cap));
        }

         WRAP_GL void DrawElements(GLenum mode,GLsizei count,GLenum type,const GLvoid *indices) {
             NATIVEGL(glDrawElements(mode, count, type, indices));
         }

        // TODO
        //PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;
        //glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
        //glGenerateMipmap(GL_TEXTURE_2D);
        WRAP_GL void GenerateMipmap(GLenum target) {
            QTGL(glGenerateMipmap(target));
        }


        WRAP_GL GLuint CreateProgram() {
            return QTGL(glCreateProgram());
        }

        WRAP_GL void LinkProgram(GLuint program) {
            QTGL(glLinkProgram(program));
        }

        WRAP_GL void GetProgramiv(GLuint program, GLenum pname, GLint* params) {
            QTGL(glGetProgramiv(program, pname, params));
        }

        WRAP_GL void GetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog) {
            QTGL(glGetProgramInfoLog(program, bufsize, length, infolog));
        }

        WRAP_GL void DeleteProgram(GLuint program) {
            QTGL(glDeleteProgram(program));
        }

        WRAP_GL void UseProgram(GLuint program) {
            QTGL(glUseProgram(program));
        }


        WRAP_GL GLuint CreateShader(GLenum type) {
            return QTGL(glCreateShader(type));
        }

        WRAP_GL void ShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length) {
            QTGL(glShaderSource(shader, count, string, length));
        }

        WRAP_GL void CompileShader(GLuint shader) {
            QTGL(glCompileShader(shader));
        }

        WRAP_GL void GetShaderiv(GLuint shader, GLenum pname, GLint* params) {
            QTGL(glGetShaderiv(shader, pname, params));
        }

        WRAP_GL void GetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog) {
            QTGL(glGetShaderInfoLog(shader, bufsize, length, infolog));
        }

        WRAP_GL void DeleteShader(GLuint shader) {
            QTGL(glDeleteShader(shader));
        }

        WRAP_GL void AttachShader(GLuint program, GLuint shader) {
            QTGL(glAttachShader(program, shader));
        }


        WRAP_GL GLint GetUniformLocation(GLuint program, const char* name) {
            return QTGL(glGetUniformLocation(program, name));
        }

        WRAP_GL void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
            QTGL(glUniformMatrix4fv(location, count, transpose, value));
        }

        WRAP_GL GLint GetAttribLocation(GLuint program, const char* name) {
            return QTGL(glGetAttribLocation(program, name));
        }

        WRAP_GL void VertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr) {
            QTGL(glVertexAttribPointer(indx, size, type, normalized, stride, ptr));
        }


        WRAP_GL void GenBuffers(GLsizei n, GLuint* buffers) {
            QTGL(glGenBuffers(n, buffers));
        }

        WRAP_GL void DeleteBuffers(GLsizei n, const GLuint* buffers) {
            QTGL(glDeleteBuffers(n, buffers));
        }

        WRAP_GL void BindBuffer(GLenum target, GLuint buffer) {
            QTGL(glBindBuffer(target, buffer));
        }

        WRAP_GL void BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) {
            QTGL(glBufferData(target, size, data, usage));
        }

        WRAP_GL void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data) {
            QTGL(glBufferSubData(target, offset, size, data));
        }

        WRAP_GL void DisableVertexAttribArray(GLuint index) {
            QTGL(glDisableVertexAttribArray(index));
        }
        WRAP_GL void EnableVertexAttribArray(GLuint index) {
            QTGL(glEnableVertexAttribArray(index));
        }
    };

#undef WRAP_GL
#undef NATIVEGL
#undef QTGL
}
