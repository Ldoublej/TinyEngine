//
// Created by ldoublej on 18-11-10.
//

#include "Texture2DArray.h"

namespace graph
{
    Texture2DArray *Texture2DArray::Create(GLenum internalFormat, GLenum filter, GLenum wrap)
    {
        Texture2DArray * tex = new Texture2DArray(internalFormat);
        if (tex->GetBufferID() == 0)
            return nullptr;

        glBindTexture(GL_TEXTURE_2D_ARRAY, tex->GetBufferID());
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, wrap);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, filter);
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
        return tex;
    }

    void Texture2DArray::Storage(GLsizei levels, GLsizei width, GLsizei height, GLsizei depth)
    {
        if (width==0 || height == 0 || depth == 0)
                return;
        glBindTexture(GL_TEXTURE_2D_ARRAY, _buffer_id);
        glTexStorage3D(GL_TEXTURE_2D_ARRAY, levels,_internalFormat, width, height,depth);
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }

    void Texture2DArray::TexImage(GLint level, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type,
                                  const void *data) {
        if (width==0 || height == 0 || depth == 0)
                return;
        glBindTexture(GL_TEXTURE_2D_ARRAY, _buffer_id);
        glTexImage3D(GL_TEXTURE_2D_ARRAY, level, _internalFormat, width, height,depth, 0, format, type, data);
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }

    void Texture2DArray::TexSubImage(GLint level, GLint xoffset, GLint yoffset, GLsizei zoffset, GLsizei width,
                                     GLsizei height,GLsizei depth, GLenum format, GLenum type, const void *data) {
        if ((width == 0 || height == 0)|| yoffset + xoffset + zoffset < 0)
                return;
        glBindTexture(GL_TEXTURE_2D_ARRAY, _buffer_id);
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, level, xoffset, yoffset,zoffset, width, height,depth, format, type, data);
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }

    void Texture2DArray::TexParameter(GLenum para, GLenum value)
    {
        glBindTexture(GL_TEXTURE_2D_ARRAY, _buffer_id);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, para, value);
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }

    void Texture2DArray::EnableMipMap() {
        glBindTexture(GL_TEXTURE_2D_ARRAY, _buffer_id);
        glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }
}