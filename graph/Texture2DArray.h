//
// Created by ldoublej on 18-11-9.
//

#ifndef SIMPLEOGL_TEXTURE2DARRAY_H
#define SIMPLEOGL_TEXTURE2DARRAY_H

#include "Texture.h"

namespace graph
{

    class Texture2DArray:public Texture
    {
    private:
        explicit Texture2DArray(GLenum internalFormat) :Texture(GL_TEXTURE_2D_ARRAY, internalFormat) { _internalFormat = internalFormat; };

    public:
        static Texture2DArray * Create(GLenum internalFormat, GLenum filter = GL_LINEAR, GLenum wrap = GL_REPEAT);

        void Storage(GLsizei levels,GLsizei width,GLsizei height,GLsizei depth);
        void TexImage(GLint level, GLsizei width, GLsizei height,GLsizei depth ,GLenum format, GLenum type, const void * data);
        void TexSubImage(GLint level,GLint xoffset,GLint yoffset,GLsizei zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const void * data);

        void TexParameter(GLenum para, GLenum value);

        void EnableMipMap();

        ~Texture2DArray() override = default;
    };

}

#endif //SIMPLEOGL_TEXTURE2DARRAY_H
