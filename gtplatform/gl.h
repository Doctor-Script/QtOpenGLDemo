#pragma once

#include <QOpenGLFunctions>


namespace gt
{
#define WRAP static inline
#define NATIVE(f) ::f
#define PLATFORM(f) _functions->f

    struct gl
    {
        static QOpenGLFunctions* _functions;

        WRAP void GenTextures(GLsizei n, GLuint *textures) {
            NATIVE(glGenTextures(n, textures));
        }

        WRAP void DeleteTextures(GLsizei n, const GLuint *textures) {
            NATIVE(glDeleteTextures(n, textures));
        }

        WRAP void BindTexture(GLenum target, GLuint texture) {
            NATIVE(glBindTexture(target, texture));
        }

        WRAP void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels) {
            NATIVE(glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels));
        }

        WRAP void TexParameteri(GLenum target, GLenum pname, GLint param) {
            NATIVE(glTexParameteri(target, pname, param));
        }

        WRAP void ClearColor(GLclampf red,GLclampf green,GLclampf blue,GLclampf alpha) {
            NATIVE(glClearColor(red, green, blue, alpha));
        }

        WRAP void Clear(GLbitfield mask) {
            NATIVE(glClear(mask));
        }

         WRAP void Enable(GLenum cap) {
            NATIVE(glEnable(cap));
        }

         WRAP void BlendFunc(GLenum sfactor, GLenum dfactor) {
            NATIVE(glBlendFunc(sfactor, dfactor));
         }

         WRAP void DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) {
             NATIVE(glDrawElements(mode, count, type, indices));
         }

        // TODO
        //PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;
        //glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
        //glGenerateMipmap(GL_TEXTURE_2D);
        WRAP void GenerateMipmap(GLenum target) {
            PLATFORM(glGenerateMipmap(target));
        }


        WRAP GLuint CreateProgram() {
            return PLATFORM(glCreateProgram());
        }

        WRAP void LinkProgram(GLuint program) {
            PLATFORM(glLinkProgram(program));
        }

        WRAP void GetProgramiv(GLuint program, GLenum pname, GLint* params) {
            PLATFORM(glGetProgramiv(program, pname, params));
        }

        WRAP void GetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog) {
            PLATFORM(glGetProgramInfoLog(program, bufsize, length, infolog));
        }

        WRAP void DeleteProgram(GLuint program) {
            PLATFORM(glDeleteProgram(program));
        }

        WRAP void UseProgram(GLuint program) {
            PLATFORM(glUseProgram(program));
        }


        WRAP GLuint CreateShader(GLenum type) {
            return PLATFORM(glCreateShader(type));
        }

        WRAP void ShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length) {
            PLATFORM(glShaderSource(shader, count, string, length));
        }

        WRAP void CompileShader(GLuint shader) {
            PLATFORM(glCompileShader(shader));
        }

        WRAP void GetShaderiv(GLuint shader, GLenum pname, GLint* params) {
            PLATFORM(glGetShaderiv(shader, pname, params));
        }

        WRAP void GetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog) {
            PLATFORM(glGetShaderInfoLog(shader, bufsize, length, infolog));
        }

        WRAP void DeleteShader(GLuint shader) {
            PLATFORM(glDeleteShader(shader));
        }

        WRAP void AttachShader(GLuint program, GLuint shader) {
            PLATFORM(glAttachShader(program, shader));
        }


        WRAP GLint GetUniformLocation(GLuint program, const char* name) {
            return PLATFORM(glGetUniformLocation(program, name));
        }

        WRAP void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
            PLATFORM(glUniformMatrix4fv(location, count, transpose, value));
        }

        WRAP void Uniform1f(GLint location, GLfloat x) {
            PLATFORM(glUniform1f(location, x));
        }

        WRAP void Uniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
            PLATFORM(glUniform4f(location, x, y, z, w));
        }

        WRAP GLint GetAttribLocation(GLuint program, const char* name) {
            return PLATFORM(glGetAttribLocation(program, name));
        }

        WRAP void VertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr) {
            PLATFORM(glVertexAttribPointer(indx, size, type, normalized, stride, ptr));
        }


        WRAP void GenBuffers(GLsizei n, GLuint* buffers) {
            PLATFORM(glGenBuffers(n, buffers));
        }

        WRAP void DeleteBuffers(GLsizei n, const GLuint* buffers) {
            PLATFORM(glDeleteBuffers(n, buffers));
        }

        WRAP void BindBuffer(GLenum target, GLuint buffer) {
            PLATFORM(glBindBuffer(target, buffer));
        }

        WRAP void BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) {
            PLATFORM(glBufferData(target, size, data, usage));
        }

        WRAP void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data) {
            PLATFORM(glBufferSubData(target, offset, size, data));
        }

        WRAP void DisableVertexAttribArray(GLuint index) {
            PLATFORM(glDisableVertexAttribArray(index));
        }
        WRAP void EnableVertexAttribArray(GLuint index) {
            PLATFORM(glEnableVertexAttribArray(index));
        }

        WRAP void PixelStorei(GLenum pname,GLint param) {
            PLATFORM(glPixelStorei(pname, param));
        }

        WRAP void GetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint* params) {
            NATIVE(glGetTexLevelParameteriv (target, level, pname, params));
        }
    };

#undef WRAP
#undef NATIVE
#undef PLATFORM
}
