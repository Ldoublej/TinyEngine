//
// Created by ldoublej on 18-11-8.
//

#ifndef TINYENGINE_CUBEMAP_H
#define TINYENGINE_CUBEMAP_H

#include "Texture.h"

namespace graph
{

    class CubeMap:public Texture
    {
    private:
        CubeMap(GLenum internalFormat) :Texture(GL_TEXTURE_CUBE_MAP, internalFormat) { _internalFormat = internalFormat; };
    public:
        static CubeMap * Create(GLenum internalFormat, GLenum filter = GL_LINEAR, GLenum wrap = GL_CLAMP_TO_EDGE);

        void Storage(GLsizei levels,GLsizei width,GLsizei height);
        void TexImage(GLint level, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * data);
        void TexParameter(GLenum para, GLenum value);

        ~CubeMap() { glDeleteTextures(1,&_buffer_id); };
    };

}


#endif //TINYENGINE_CUBEMAP_H
