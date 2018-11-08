#ifndef TINYENGINE_TEXTURE2D_H
#define TINYENGINE_TEXTURE2D_H

#include "Texture.h"

namespace graph
{
	class Texture2D :public Texture
	{
	private:
		Texture2D(GLenum internalFormat) :Texture(GL_TEXTURE_2D, internalFormat) { _internalFormat = internalFormat; };

	public:
		static Texture2D * Create(GLenum internalFormat, GLenum filter = GL_LINEAR, GLenum wrap = GL_REPEAT);

		void Storage(GLsizei levels,GLsizei width,GLsizei height);
		void TexImage(GLint level, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * data);
		void TexSubImage(GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * data);
		void TexImageFromFBO(GLint level,GLint x,GLint y,GLsizei width,GLsizei height);

		void TexParameter(GLenum para, GLenum value);

		void EnableMipMap();

		~Texture2D() { glDeleteTextures(1,&_buffer_id); };
	};
}

#endif