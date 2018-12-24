//
// Created by ldoublej on 18-11-8.
//

#include "CubeMap.h"

namespace graph
{
    CubeMap * CubeMap::Create(GLenum internalFormat, GLenum filter , GLenum wrap)
    {
        auto * tex = new CubeMap(internalFormat);
        if (tex->GetBufferID() == 0)
            return nullptr;

        glBindTexture(GL_TEXTURE_CUBE_MAP, tex->GetBufferID());
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrap);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wrap);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, filter);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        return tex;
    }
    void CubeMap::Storage(GLsizei levels, GLsizei width, GLsizei height)
    {
        if (width==0 || height == 0)
            return;
        glBindTexture(GL_TEXTURE_CUBE_MAP, _buffer_id);
        glTexStorage2D(GL_TEXTURE_CUBE_MAP, levels,_internal_format, width, height);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
    void CubeMap::TexImage(GLenum target,GLint levels, GLsizei width, GLsizei height,GLenum format,GLenum type, const void * data)
    {
        if (width == 0 || height == 0)
            return;
        glBindTexture(GL_TEXTURE_CUBE_MAP, _buffer_id);
        glTexImage2D(target, levels, _internal_format, width, height, 0, format, type, data);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void CubeMap::TexParameter(GLenum para, GLenum value)
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, _buffer_id);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, para, value);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void CubeMap::EnableMipMap() {
        glBindTexture(GL_TEXTURE_CUBE_MAP, _buffer_id);
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

}