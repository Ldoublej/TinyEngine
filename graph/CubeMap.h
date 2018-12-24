//
// Created by ldoublej on 18-11-8.
//

#ifndef SIMPLEOGL_CUBEMAP_H
#define SIMPLEOGL_CUBEMAP_H

#include "Texture.h"

namespace graph
{
    class CubeMap:public Texture
    {
    private:
        explicit CubeMap(GLenum internalFormat) :Texture(GL_TEXTURE_CUBE_MAP, internalFormat) {};
    public:
        static CubeMap * Create(GLenum internalFormat, GLenum filter = GL_LINEAR, GLenum wrap = GL_CLAMP_TO_EDGE);
        void Storage(GLsizei levels,GLsizei width,GLsizei height);
        void TexImage(GLenum target,GLint levels, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * data);
        void TexParameter(GLenum para, GLenum value);
        void EnableMipMap();
        ~CubeMap() override = default;
    };

}


#endif //SIMPLEOGL_CUBEMAP_H
